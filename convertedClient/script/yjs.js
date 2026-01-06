import * as Y from "yjs";
import { WebrtcProvider } from "y-webrtc";
import { IndexeddbPersistence } from "y-indexeddb";

const ydoc = new Y.Doc();
const docName = "test";
// clients connected to the same room-name share document updates
const provider = new WebrtcProvider("test-room", ydoc, {
  signaling: ["ws://localhost:4444"],
});

const persistence = new IndexeddbPersistence(docName, ydoc);
const yarray = ydoc.get("array", Y.Array);
yarray.observe((event) => {
  console.log("yarray changed:", yarray.toArray());
});

export default ydoc;
