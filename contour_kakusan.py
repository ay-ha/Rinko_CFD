
import glob
import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as animation


file_list = glob.glob('2Dkekka*.csv')

file_num = []
for i, file_name in enumerate(file_list):
    file_num.append(float(file_name.split('2Dkekka')[1].split('.csv')[0]))
file_num = sorted(file_num)

ims = []
for i, num in enumerate(file_num):
    print(num)
    file_name = '2Dkekka{:03d}.csv'.format(int(num))
    df = pd.read_csv(file_name, sep=',', index_col=0)
    df = df.loc[:, ~df.columns.str.contains('^Unnamed')]
    x_array = np.array(df.columns.tolist(), dtype='float')
    y_array = np.array(df.index.tolist(), dtype='float')

    fig, ax = plt.subplots()
    if i==0:
        z_min = df.min().min()
        z_max = df.max().max()
        z_min = 0.0
        z_max = 100.0
    X, Y = np.meshgrid(x_array, y_array)
    Z = []
    for y in df.index:
        Z_tmp = []
        for x in df.columns:
            Z_tmp.append(df.loc[y, x])
        Z.append(Z_tmp)
    im = ax.pcolormesh(X, Y, Z, shading='auto', cmap='jet', vmin=z_min, vmax=z_max)
    #im = ax.pcolormesh(X, Y, Z, shading='auto', cmap='gist_ncar', vmin=z_min, vmax=z_max)

    cbar=fig.colorbar(im)
    ims.append(im)
    plt.savefig('contour_{:04}'.format(i))

# ani = animation.ArtistAnimation(fig, ims)
# ani.save('anim.gif', writer="imagemagick")

