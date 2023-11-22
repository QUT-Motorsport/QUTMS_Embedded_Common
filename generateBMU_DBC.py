import math

output = 'BMU_DBC.txt'

num_cmu = 20
num_volt = 14
num_temp = 16

pc_volt = math.ceil(num_volt/3)
pc_temp = math.ceil(num_temp/6)

print(num_cmu, num_volt, num_temp, pc_volt, pc_temp)

id_TxV_N0P0 = 136609792
id_TxT_N0P0 = 136610816

print(hex(id_TxV_N0P0), hex(id_TxT_N0P0))

f = open(output, 'w')

# voltages
for i in range(0, num_cmu):
    for j in range(0, pc_volt):
        id = (id_TxV_N0P0 | (i << 4) | (j)) | (1 << 31)
        line = f'BO_ {id} BMU_TransmitVoltage_N_{i}_P_{j}: 8 Vector__XXX'
        f.write(line)
        f.write('\n')
        print(hex(id), line)

        for k in range(0, 3):
            voltNum = j*3 + k
            if (voltNum >= num_volt):
                break
            line = f' SG_ BMU_Voltage_C{i}_{voltNum} : {k*16}|16@1+ (1,0) [0|0] "" Vector__XXX'
            f.write(line)
            f.write('\n')
            print(hex(id), line)

        line = f' SG_ BMU_Voltage_Age_C{i} : {48}|16@1+ (1,0) [0|0] "" Vector__XXX'
        f.write(line)
        f.write('\n')
        print(hex(id), line)
        f.write('\n')

# temperatures
for i in range(0, num_cmu):
    for j in range(0, pc_temp):
        id = (id_TxT_N0P0 | (i << 4) | (j)) | (1 << 31)
        line = f'BO_ {id} BMU_TransmitTemperature_N_{i}_P_{j}: 8 Vector__XXX'
        f.write(line)
        f.write('\n')
        print(hex(id), line)

        for k in range(0, 6):
            tempNum = j*6 + k
            if (tempNum >= num_temp):
                break
            line = f' SG_ BMU_Temperature_C{i}_{tempNum} : {k*8}|8@1+ (1,0) [0|0] "" Vector__XXX'
            f.write(line)
            f.write('\n')
            print(hex(id), line)

        line = f' SG_ BMU_Temperature_Age_C{i} : {48}|16@1+ (1,0) [0|0] "" Vector__XXX'
        f.write(line)
        f.write('\n')
        print(hex(id), line)
        f.write('\n')
f.close()