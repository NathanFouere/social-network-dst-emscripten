import * as Y from "yjs";
import { WebrtcProvider } from "y-webrtc";

const ydoc = new Y.Doc();
// clients connected to the same room-name share document updates
const provider = new WebrtcProvider("your-room-name", ydoc, {
  password: "optional-room-password",
});
const yarray = ydoc.get("array", Y.Array);
