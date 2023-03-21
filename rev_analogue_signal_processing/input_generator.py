import numpy as np
from circuit import ZLCircuit, simulate_chained_circuits

from flag import FLAG
import soundfile as sf

duration = 240
SAMPLE_RATE = 0x4000
samples = int(duration * SAMPLE_RATE)

def encode_flag(flag):
    vin = np.random.uniform(-1, 1, samples)
    for i in range(len(flag)):
        vout = simulate_chained_circuits([ZLCircuit(1j * ord(flag[i]), 1)], vin, duration, SAMPLE_RATE)[0]
        sf.write(f'new_audio/encoded{i}.wav', np.real(vout).astype('float64'), SAMPLE_RATE, subtype='DOUBLE')
        vin = vout
        print(f'encoded {i} of {len(flag)} characters')

if __name__ == '__main__':
    encode_flag(FLAG)
