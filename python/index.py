import numpy as np
from sklearn.cluster import KMeans
data = np.random.rand(50000,4)

import time
start_time = time.time()
clf = KMeans(n_clusters= 6, n_init= 1, max_iter= 1000, tol=1e-20000000, n_jobs=1)
clf.fit(data)

t = (time.time() - start_time)
print("--- %s seconds ---" % (t))