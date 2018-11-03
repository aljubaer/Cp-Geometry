# include "includes.cpp"

typedef vector <vector <double> > Matrix;
typedef vector <double> SolvSet;

class GaussianElemination{
private:
    int dimen;
    Matrix aug;
    SolvSet solution;
    void solve(){
        int i, j, k, l; double t;
        for (j = 0; j < dimen-1; j++){
            l = j;
            for (i = j + 1; i < dimen; i++){
                if (fabs(aug[i][j]) > fabs(aug[l][j]))
                    l = i;
            }
            for (k = j; k <= dimen; k++){
                t = aug[j][k];
                aug[j][k] = aug[l][k];
                aug[l][k] = t;
            }
            if (fabs(aug[j][j]) < EPS){
                solved = false;
                return;
            }
            for (i = j + 1; i < dimen; i++){
                for (k = dimen; k >= j; k--){
                    aug[i][k] -= aug[j][k] * aug[i][j] / aug[j][j];
                }
            }
        }
        for (j = dimen - 1; j >= 0; j--){
            t = 0.0;
            for (k = j + 1; k < dimen; k++){
                t += aug[j][k] * solution[k];
            }
            solution[j] = (aug[j][dimen] - t) / aug[j][j];
        }
        return;
    }
public:
    bool solved = true;
    GaussianElemination(int dim, Matrix& _aug){
        dimen = dim;
        aug.resize(dim);
        for (int i = 0; i < dim; i++){
            for (int j = 0; j <= dim; j++){
                cout << _aug[i][j] << '\t';
                aug[i].push_back(_aug[i][j]);
            }
            cout << '\n';
        }
        solution.resize(dim);
    }
    bool isSolvable(){ solve(); return solved; }
    SolvSet getSolution(){ return solution; }
};

int main(){

    int n = 3;
    double v[n][n+1] = {
        {1, 1, 2, 9},
        {2, 4, -3, 1},
        {3, 6, -5, 0}
    };
    Matrix m(n);
    for (int i = 0; i < n; i++){
        for (int j = 0; j <= n; j++){
            m[i].push_back(v[i][j]);
        }
    }
    GaussianElemination g(n, m);
    if (g.isSolvable()){
        SolvSet s = g.getSolution();
        cout << "Solutions: ";
        for (double ans: s)
            cout << ans << ' ';
        cout << '\n';
    }
}
