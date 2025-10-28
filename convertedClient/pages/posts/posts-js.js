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

  // Construire IntList et StringList à partir des tableaux JS
  const IntList = di.module.IntList;
  const StringList = di.module.StringList;
  const ids = new IntList();
  const types = new StringList();
  for (const id of mediaIdsArr) ids.push_back(id);
  for (const t of mediaTypesArr) types.push_back(t);

  const req_id = Date.now();
  const user_id = 1; // mock très simple

  try {
    di.composePostHandler.ComposePost(
      req_id,
      username,
      user_id,
      text,
      ids,
      types,
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
    note: "Appel via register_vector (IntList/StringList)"
  };

  output.textContent = JSON.stringify(out, null, 2);
});
