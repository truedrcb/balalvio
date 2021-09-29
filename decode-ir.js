import { irCodes } from "./ir-codes.js";

console.log("Decoding...");
for (const [brand, buttons] of Object.entries(irCodes)) {
    for (const [button, millis] of Object.entries(buttons)) {
        console.log(`${brand}: ${button} - length: ${millis.length}`);
        if (millis.length < 3) {
            console.error("Length < 3");
            continue;
        } 
        if ((millis.length % 2) != 1) {
            console.error("Length is not odd");
            continue;
        }
        var maxUp = 0, maxDown = 0, minUp = millis[0], minDown = millis[1];
        for (var i = 2; i < millis.length; i++) {
            if (millis[i] > maxUp) {
                maxUp = millis[i];
            }
            if (millis[i] < minUp) {
                minUp = millis[i];
            }
            i++;
            if (millis[i] > maxDown) {
                maxDown = millis[i];
            }
            if (millis[i] < minDown) {
                minDown = millis[i];
            }
        }
        console.log(`Up: ${minUp} to ${maxUp}; Down: ${minDown} to ${maxDown}`)

        var code = "";
        for (var i = 2; i < millis.length - 1; i+=2) {
            var up = millis[i];
            var down = millis[i+1]

            if ( up < 20 || down < 20) {
                code += ".";
                continue;
            }
            if ( down > (up * 0.8) && down < (up * 1.4)) {
                code += "0";
                continue;
            }
            if ( down > (up * 1.8) && down < (up * 4)) {
                code += "1";
                continue;
            }
            code += "?";
        }
        console.log(`Binary: ${code}`)

    }
}
  
console.log("End.");
