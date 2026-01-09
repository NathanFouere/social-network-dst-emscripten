import * as Y from "yjs";
import { WebrtcProvider } from "y-webrtc";
import { IndexeddbPersistence } from "y-indexeddb";

const ydoc = new Y.Doc();
const docName = "test";
// clients connected to the same room-name share document updates
const provider = new WebrtcProvider("test-room", ydoc, {
  signaling: ["ws://10.144.199.199:4444"],
  peerOpts: {
    config: {
      iceServers: [
        { urls: ['stun:stun.l.google.com:19302', 'stun:global.stun.twilio.com:3478'] }
      ]
    }
  }
});
provider.on("status", (event) => {
  console.log("webrtc status:", event);
});

const persistence = new IndexeddbPersistence(docName, ydoc);
const yarray = ydoc.get("array", Y.Array);
yarray.observe((event) => {
  console.log("yarray changed:", yarray.toArray());
});

persistence.whenSynced.then(() => {
  console.log("IndexedDB ready");
  const posts = ydoc.getArray("posts");
  console.log("Current posts in YArray:", posts.toArray());
});

provider.on('status', event => {
  console.log('WebRTC provider status event:', event);
  const statusEl = document.getElementById('connection-status');
  if (statusEl) {
    if (event.connected) {
      statusEl.className = 'badge badge-warning';
      statusEl.innerText = 'Signaling connected';
    } else {
      statusEl.className = 'badge badge-secondary';
      statusEl.innerText = 'Offline';
    }
  }
});

provider.on('peers', event => {
  console.log('WebRTC peers event:', event);
  const webrtcPeersCount = event.webrtcPeers ? event.webrtcPeers.length || event.webrtcPeers.size || 0 : 0;
  const bcPeersCount = event.bcPeers ? event.bcPeers.length || event.bcPeers.size || 0 : 0;
  const peersCount = webrtcPeersCount + bcPeersCount;
  console.log('Detected peers count (WebRTC + BC):', peersCount);

  const statusEl = document.getElementById('connection-status');
  if (statusEl) {
    if (peersCount > 0) {
      statusEl.className = 'badge badge-success';
      statusEl.innerText = `Connected (${peersCount} peers)`;
    } else {
      statusEl.className = 'badge badge-warning';
      statusEl.innerText = 'Waiting for peers...';
    }
  }
});

provider.on('synced', synced => {
  console.log('WebRTC provider synced:', synced);
  const posts = ydoc.getArray("posts");
  console.log('Current posts in YArray:', posts.toArray());
});

export { provider };
export default ydoc;