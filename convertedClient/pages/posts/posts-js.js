import di from '../../di.js'

const form = document.getElementById('postform');
const output = document.getElementById('output');

function parseCommaList(s) {
  return s.split(',').map(v => v.trim()).filter(v => v.length > 0);
}

form.addEventListener('submit', (ev) => {
  ev.preventDefault();

  const username = document.getElementById('username-input').value;
  const text = document.getElementById('text-input').value;
  const mediaIdsRaw = document.getElementById('media-ids-input').value;
  const mediaTypesRaw = document.getElementById('media-types-input').value;

  const mediaIdsArr = parseCommaList(mediaIdsRaw).map(x => parseInt(x, 10));
  const mediaTypesArr = parseCommaList(mediaTypesRaw);

  // Build MediaList (Module.MediaList) and other objects
  const module = di.module;

  // Create a Post instance
  const post = new module.Post();

  // Generate a unique id via UniqueIdHandler
  const post_id = di.uniqueIdHandler.ComposeUniqueId();
  post.post_id = post_id;
  post.req_id = post_id; // reuse
  post.text = text;

  // Set creator using UserHandler helper (already exposed)
  const creator = di.userHandler.ComposeCreatorWithUserId(post_id, username);
  // set creator via property
  post.creator = creator;

  // Build media vector
  const mediaList = new module.MediaList();
  for (let i = 0; i < mediaIdsArr.length; i++) {
    const m = new module.Media();
    m.media_id = mediaIdsArr[i];
    m.media_type = mediaTypesArr[i] || '';
    mediaList.push_back(m);
  }
  post.media = mediaList;

  // Empty mentions/urls for this simulation - assign directly to avoid unused var warnings
  post.user_mentions = new module.UserMentionList();
  post.urls = new module.UrlList();

  // timestamp
  post.timestamp = Date.now();

  // post type
  post.post_type = module.PostType.POST;

  // Call StorePost (this will currently log on the C++ side)
  try {
    di.postStorageHandler.StorePost(post);
  } catch (err) {
    console.error('StorePost failed:', err);
  }

  // Read back (the C++ ReadPost currently returns a fake post)
  let ret;
  try {
    ret = di.postStorageHandler.ReadPost(post_id);
  } catch (err) {
    console.error('ReadPost failed:', err);
  }

  // Display both the created post and the value returned by ReadPost
  const out = {
    created: {
      post_id: post.post_id,
      text: post.text,
      media_count: mediaList.size(),
      media0: mediaList.size() ? { id: mediaList.get(0).media_id, type: mediaList.get(0).media_type } : null,
      creator: { user_id: creator.user_id, username: creator.username },
      post_type: post.post_type,
      timestamp: post.timestamp
    },
    returned: ret ? {
      post_id: ret.post_id,
      text: ret.text,
      post_type: ret.post_type,
      timestamp: ret.timestamp
    } : null
  };

  output.textContent = JSON.stringify(out, null, 2);

  // Note: we don't delete the WASM-backed objects here for brevity; in a real app free memory with .delete()
});
