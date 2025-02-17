#pip install numpy, matplotlib, scikit-learn
#explicitly scikit-learn, sklearn is deprecated and you cannot import it
import numpy as np
import matplotlib.pyplot as plt
from sklearn.linear_model import RANSACRegressor
from sklearn.preprocessing import PolynomialFeatures
from sklearn.pipeline import make_pipeline

debug = True

plt.style.use('dark_background')

def load_data(filepath, skip_rows=6):
    """
    Description:
    Loads an exported labquest datafile (in txt format)
    ASSUMES that the two numeric columns provided are time and force

    Params:
    filepath (String) (Required) Relative filepath to access
    Skiprows (int) (Default of 6) Amount of header rows at the top to skip

    Returns:
    Time (array)
    Force (array)
    """
    data = np.loadtxt(filepath, skiprows=skip_rows)
    time = data[:, 0]
    force = data[:, 1]

    if (debug):
        print(f"Returning data of filepath {filepath}\nWith time = {time}\nAnd data = {data}")
    return time, force

#Relative data paths
#all data should be under DATA/...
data1_path = r"Data Analysis\Data\data1.txt"
data2_path = r"Data Analysis\Data\data2.txt"
data3_path = r"Data Analysis\Data\data3.txt"

#Load time and force arrays
time1, force1 = load_data(data1_path)
time2, force2 = load_data(data2_path)
time3, force3 = load_data(data3_path)

#Combine all time and force data into single arrays
all_time = np.concatenate((time1, time2, time3))
all_force = np.concatenate((force1, force2, force3))

if (debug):
    print(f"Combined time data: {all_time}")
    print(f"Combined force data: {all_force}")

#Plot each graph independently on one graph
plt.plot(time1, force1, label="Data 1", color="blue")
plt.plot(time2, force2, label="Data 2", color="red")
plt.plot(time3, force3, label="Data 3", color="green")

#Fit a RANSAC regressor model to the combined data
model = make_pipeline(PolynomialFeatures(1), RANSACRegressor())
model.fit(all_time.reshape(-1, 1), all_force)

ransac = model.named_steps['ransacregressor']
slope = ransac.estimator_.coef_[1]
intercept = ransac.estimator_.intercept_

#Predict the line of best fit
line_x = np.linspace(all_time.min(), all_time.max(), 100)
line_y = model.predict(line_x.reshape(-1, 1))

if (debug):
    print(f"Line of best fit X values: {line_x}")
    print(f"Line of best fit Y values: {line_y}")

#(Finally) Plot the line of best fit
plt.plot(line_x, line_y, linestyle='--', color="yellow", label="Best Fit Line")

if (debug):
    print(f"\n\nSlope of the line of best fit: {slope}")
    print(f"Vertical shift of the line of best fit: {intercept}")
    
#Add axis labels, title, and legend.
plt.xlabel("Time (s)")
plt.ylabel("Force (N)")
plt.title("Pinch Grip Test Trials")
plt.legend()

plt.show()