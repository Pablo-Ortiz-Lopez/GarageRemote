function pulsesToBytes(bits) {
    const numBits = bits.length
    const numBytes = Math.ceil(numBits / 8);
    const bytes = [];

    for (let i = 0; i < numBytes; i++) {
        let byte = 0;
        for (let j = 0; j < 8; j++) {
            const bitIndex = i * 8 + j;
            if (bitIndex < numBits) {
                if (bits[bitIndex]) {
                    byte |= (1 << (7 - j));
                }
            }
        }
        bytes.push(byte);
    }

    return bytes;
}

pisoOnePulse = [1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0]
pisoZeroPulse = [1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0]

const codes = [
    {
        name: "Casa 1",
        code: [1, 1, 0, 1, 1, 0, 0, 0, 1, 1, 0, 1, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0],
        onePulse: [1, 1, 1, 0],
        zeroPulse: [1, 0, 0, 0]
    },
    {
        name: "Casa 2",
        code: [1, 1, 0, 1, 1, 0, 0, 0, 1, 1, 0, 1, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0],
        onePulse: [1, 1, 1, 0],
        zeroPulse: [1, 0, 0, 0]
    },
    {
        name: "Javi 1",
        code: [1, 1, 0, 1, 1, 1, 1, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 1, 1, 1, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0],
        onePulse: [0, 1, 1, 1],
        zeroPulse: [0, 0, 0, 1]
    },
    {
        name: "Javi 2",
        code: [1, 1, 0, 1, 1, 1, 1, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0, 1, 1, 0, 1, 1, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0],
        onePulse: [0, 1, 1, 1],
        zeroPulse: [0, 0, 0, 1]
    },
    {
        name: 'Piso 1',
        code: [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 1, 0, 1, 1, 1, 0, 0, 0],
        onePulse: pisoOnePulse,
        zeroPulse: pisoZeroPulse,
    },
    {
        name: 'Piso 2',
        code: [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 1, 0, 1, 1, 0, 1, 0, 0],
        onePulse: pisoOnePulse,
        zeroPulse: pisoZeroPulse,
    },
]

maxBytes = 0;
for (const code of codes) {
    bits = []
    for (const value of code.code) {
        if (value) {
            bits = [...bits, ...code.onePulse]
        } else {
            bits = [...bits, ...code.zeroPulse]
        }
    }
    code.bytes = pulsesToBytes(bits)
    maxBytes = Math.max(maxBytes, code.bytes.length)
}

console.log(`uint8_t codeLengths[${codes.length}]={ ${codes.map(code => code.bytes.length).join(',')} };`)
console.log(`uint8_t codes[${codes.length}][${maxBytes}]= {`)
for (const code of codes) {
    const hexArray = code.bytes.map(number => '0x' + number.toString(16).toUpperCase());
    console.log(`   { ${hexArray.join(', ')} }, // ${code.name}`)
}
console.log('};')