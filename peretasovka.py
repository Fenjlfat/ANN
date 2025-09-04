import numpy as np
data_table = np.genfromtxt("ANN_ALL_SPH_MM_CU_V1D5_1_POR.txt") #open and read file
np.random.shuffle(data_table)
np.savetxt("ANN_ALL_SPH_MM_CU_V1D5_1_POR_random.txt", data_table, fmt="%.7f")