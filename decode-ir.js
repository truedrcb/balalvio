import { irCodes } from "./ir-codes.js";

console.log("Decoding...");
for (const [brand, buttons] of Object.entries(irCodes)) {
    for (const [button, millis] of Object.entries(buttons)) {
        console.log(`${brand}: ${button} - ${millis.length}`);
    }
}
  
console.log("End.");
