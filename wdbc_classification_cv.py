import numpy as np
from sklearn import (datasets, tree, model_selection, naive_bayes, ensemble, neighbors)

def load_wdbc_data(filename):
    class WDBCData:
        data          = [] # Shape: (569, 30)
        target        = [] # Shape: (569, )
        target_names  = ['malignant', 'benign']
        feature_names = ['mean radius', 'mean texture', 'mean perimeter', 'mean area', 'mean smoothness', 'mean compactness', 'mean concavity', 'mean concave points', 'mean symmetry', 'mean fractal dimension',
                         'radius error', 'texture error', 'perimeter error', 'area error', 'smoothness error', 'compactness error', 'concavity error', 'concave points error', 'symmetry error', 'fractal dimension error',
                         'worst radius', 'worst texture', 'worst perimeter', 'worst area', 'worst smoothness', 'worst compactness', 'worst concavity', 'worst concave points', 'worst symmetry', 'worst fractal dimension']
    wdbc = WDBCData()
    with open(filename) as f:
        for line in f.readlines():
            items = line.split(',')
            wdbc.target.append(0 if(items[1]=='M') else 1)        # TODO #1) Add the true label (0 for M / 1 for others)
            wdbc.data.append([float(x) for x in items[2:32]])         # TODO #1) Add 30 attributes (as floating-point numbers)
        wdbc.data = np.array(wdbc.data)
    return wdbc

if __name__ == '__main__':
    # Load a dataset
    wdbc = load_wdbc_data('data/wdbc.data')     # TODO #1) Implement 'load_wdbc_data()'
    # Train a model
    model = ensemble.AdaBoostClassifier(n_estimators=50, learning_rate=1.0, algorithm='SAMME')
    # TODO  adaboosclassifier : 17점 > gradient boosting classifier : 16점 > randomforestclassifier : 16점
    cv_results = model_selection.cross_validate(model, wdbc.data, wdbc.target, cv=5, return_train_score=True)
    # Evaluate the model
    acc_train = np.mean(cv_results['train_score'])
    acc_test = np.mean(cv_results['test_score'])
    print(f'* Accuracy @ training data: {acc_train:.3f}')
    print(f'* Accuracy @ test data: {acc_test:.3f}')
    print(f'* Your score: {max(10 + 100 * (acc_test - 0.9), 0):.0f}')
