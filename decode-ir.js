import { irCodes } from "./ir-codes.js";

console.log("Decoding...");
var codes = {};
for (const [brand, buttons] of Object.entries(irCodes)) {
    codes[brand] = {};
    for (const [button, millis] of Object.entries(buttons)) {
        var ms = [];
        if (typeof millis === 'string') {
            ms.push(4500);
            ms.push(4500);
            for (let c of millis) {
                if (c === '0') {
                    ms.push(480);
                    ms.push(520);
                    continue;
                }
                if (c === '1') {
                    ms.push(480);
                    ms.push(1520);
                    continue;
                }
                if (c === '|') {
                    ms.push(480);
                    ms.push(4510);
                    continue;
                }
            }
            ms.push(460);
        } else {
            ms = millis;
        }
        codes[brand][button] = ms;

        console.log(`${brand}: ${button} - length: ${ms.length}`);
        if (ms.length < 3) {
            console.error("Length < 3");
            continue;
        } 
        if ((ms.length % 2) != 1) {
            console.error("Length is not odd");
            continue;
        }
        
        analyzeMaxMin(ms);

        var code = "";
        for (var i = 2; i < ms.length - 1; i+=2) {
            var up = ms[i];
            var down = ms[i+1]

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
            if ( down > (up * 4) && down < (up * 13)) {
                code += "|";
                continue;
            }
            console.error(`Error[${i}]: ${up}-${down}`)
            code += "?";
        }
        console.log(`Binary: ${code}`)

    }
}


console.log("Code for Arduino:");
for (const [brand, buttons] of Object.entries(codes)) {
    for (const [button, millis] of Object.entries(buttons)) {
        let arrayLength = millis.length + 1;

        console.log(`void send_${brand}_${button}() {`);
        console.log(`\tuint16_t raw_data[${arrayLength}] = {${millis},1000};`);
        console.log(`\tsend_raw(raw_data, ${arrayLength}, "${brand} - ${button}");`);
        console.log(`}`);
        console.log(``);
    }
}

console.log("End.");

function analyzeMaxMin(millis) {
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
    console.log(`Up: ${minUp} to ${maxUp}; Down: ${minDown} to ${maxDown}`);
}

