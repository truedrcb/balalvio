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

        var info = {millis:ms};
        codes[brand][button] = info;

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
        var binLength = 0;
        var binCode = 0;

        //class IRsendBase {
        //    public:
        //      IRsendBase();
        //      void sendGeneric(uint32_t data,  uint8_t numBits,
        //            uint16_t headMark, uint16_t headSpace, uint16_t markOne,
        //            uint16_t markZero, uint16_t spaceOne, uint16_t spaceZero,
        //            uint8_t kHz, bool stopBits, uint32_t maxExtent=0);

        info.headMark = ms[0];
        info.headSpace = ms[1];
        info.stopBits = true;
        info.markOne = 0;
        info.markZero = 0;
        info.spaceOne = 0;
        info.kHz = 38;
        info.spaceZero = 0;
        for (var i = 2; i < ms.length - 1; i+=2) {
            var up = ms[i];
            var down = ms[i+1]

            if ( up < 20 || down < 20) {
                code += ".";
                continue;
            }
            if ( down > (up * 0.8) && down < (up * 1.4)) {
                code += "0";
                binCode <<= 1;
                binLength++;

                info.markZero = up;
                info.spaceZero = down;

                continue;
            }
            if ( down > (up * 1.8) && down < (up * 4)) {
                code += "1";
                binCode <<= 1;
                binCode |= 1;
                binLength++;

                info.markOne = up;
                info.spaceOne = down;

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
        console.log(`Hex: 0x${Number(binCode).toString(16)} (length: ${binLength})`)
        info.binCode = binCode;
        info.binLength = binLength;
    }
}


console.log("Code for Arduino:");
for (const [brand, buttons] of Object.entries(codes)) {
    for (const [button, info] of Object.entries(buttons)) {
        let millis = info.millis;
        let arrayLength = millis.length + 1;

        console.log(`// 0x${Number(info.binCode).toString(16)} ${info.binLength}`);
        console.log(`void send_${brand}_${button}() {`);
        if (info.binLength <= 32) {
            console.log(`  send_generic(0x${Number(info.binCode).toString(16)}, ${info.binLength}, ${info.headMark}, ${info.headSpace}, ${info.markOne}, ${info.markZero}, ${info.spaceOne}, ${info.spaceZero}, ${info.kHz}, ${info.stopBits}, "${brand} - ${button}");`);
        } else {
            console.log(`  uint16_t raw_data[${arrayLength}] = {${millis},10000};`);
            console.log(`  send_raw(raw_data, ${arrayLength}, "${brand} - ${button}");`);
        }
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

