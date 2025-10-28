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

  const req_id = Date.now();
  const user_id = 1; // mock très simple

  try {
    di.composePostHandler.ComposePost(
      req_id,
      username,
      user_id,
      text,
      mediaIdsArr,
      mediaTypesArr,
      di.module.PostType.POST
    );
  } catch (err) {
    console.error('ComposePost failed:', err);
  }

  const out = {
    sent: {
      req_id,
      username,
      user_id,
      text,
      media_ids: mediaIdsArr,
      media_types: mediaTypesArr,
      post_type: 'POST'
    },
    note: "Mock: appel simple de ComposePost (voir console pour logs C++)"
  };

  output.textContent = JSON.stringify(out, null, 2);
});
