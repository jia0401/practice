#include <iostream>
#include <vector>
using namespace std;

int method()
{
	cout << "请输入已知条件满足第几边界条件：";
	int n;
	cin >> n;
	return n;
}
class equation
{
public:
	vector<vector<double>> A;
	int line;
	void com_b(int i)
	{
		int pre = i;
		int h = i;
		int max = i;
		while (i < line)
		{
			if (abs(A[i][h] > abs(A[max][h])))
				max = i;
			i++;
		}
		swap(A[pre], A[max]);
		return;
	}
	void subtract()
	{
		int times = 0;
		while (times < line)
		{
			com_b(times);
			int i = times + 1;
			while (i < line)
			{
				double tmp = -A[i][times] / A[times][times];
				for (int j = 0; j < line + 1; j++)
				{
					A[i][j] = A[i][j] + A[times][j] * tmp;
				}
				i++;
			}
			times++;
		}
		return;
	}
	vector<double> get_result()
	{
		vector<double> b;
		for (int i = 0; i < line; i++)
			b.push_back(0);
		int cur = line - 1;
		while (cur > -1)
		{
			double sum = A[cur][line];
			int t = line-1;
			while (t > 0)
			{
				sum -= A[cur][t] * b[t];
				t--;
			}
			b[cur] = sum / A[cur][cur];
			cur--;
		}
		return b;
	}
};
void get_paras(vector<double> x,vector<double> y,vector<double>& L, vector<double>& U, vector<double>& D, vector<double>& h)
{
	for (int i = 0; i < x.size() - 1; i++)
	{
		h.push_back(x[i + 1] - x[i]);
	}
	L.push_back(0);
	U.push_back(0);
	for (int i = 1; i < h.size(); i++)
	{
		L.push_back(h[i] / (h[i] + h[i - 1]));
		U.push_back(h[i - 1] / (h[i] + h[i - 1]));
		D.push_back( 3 * (U[i] * (y[i + 1] - y[i]) / h[i] + L[i]*(y[i] - y[i - 1]) / h[i - 1]));
	}
	return;
}

vector<double> method1(vector<double> L,vector<double> U,vector<double> D,int line)
{
	cout << "请分别输入端点处的导数：";
	vector<double>M;
	double m0,mn;
	cin >> m0 >> mn;
	M.push_back(m0);
	equation m1;
	vector<vector<double>> A1(line, vector<double>(line + 1,0));
	for (int i = 0; i < line; i++)
	{
		A1[i][i] = 2;
		if (i < line - 1)
		{
			A1[i][i + 1] = U[i+1];
		}
		if (i < line && i>0)
		{
			A1[i][i - 1] = L[i + 1];
		}
		if (i == 0)
			A1[i][line] = D[i] - L[i + 1] * m0;
		if (i == line - 1)
			A1[i][line] = D[i] - U[i + 1] * mn;
	}
	m1.A = A1;
	m1.line = line;
	m1.subtract();
	vector<double>t=m1.get_result();
	for (int i = 0; i < t.size(); i++)
		M.push_back(t[i]);
	M.push_back(mn);
	return M;
}
void output(vector<double> a, vector<double> x, vector<double> y, vector<double> h)
{
	for (int i = 0; i < x.size()-1; i++)
	{
		cout << "x∈[ " << x[i] << " , " << x[i + 1] << "] 时：" << endl;
		cout << "S(x) = (1+2*（x-" << x[i] << ")/" << h[i] << "*((x-" << x[i + 1] << ")/" << -h[i] << ")**2*" << y[i];
		cout << " +(1+2*（x-" << x[i + 1] << ")/" << -h[i] << "*((x-" << x[i] << ")/" << h[i] << ")**2*" << y[i + 1];
		cout << "+(x-" << x[i] << ")*((x-" << x[i + 1] << ")/" << -h[i] << ")**2*" << a[i];
		cout << "+(x-" << x[i+1] << ")*((x-" << x[i] << ")/" << h[i] << ")**2*" << a[i+1];
		cout << endl;
	}
}

vector<double> method2(vector<double> h,vector<double> y,vector<double> L, vector<double> U, vector<double> D, int line)
{
	cout << "请分别输入端点处的二阶导数：";
	vector<double>M;
	double f0, fn;
	cin >> f0 >> fn;
	equation m1;
	vector<vector<double>> A1(line, vector<double>(line + 1, 0));
	for (int i = 0; i < line; i++)
	{
		A1[i][i] = 2;
		A1[0][1] = 1;
		A1[line - 1][line - 2] = 1;
		if (i>0&&i < line - 1)
		{
			A1[i][i + 1] = U[i];
		}
		if (i < line-1 && i>0)
		{
			A1[i][i - 1] = L[i];
		}
		if (i == 0)
			A1[i][line] = 3 * (y[1] - y[0]) / h[0] - h[0] / 2 * f0;
		if (i == line - 1)
			A1[i][line] = 3 * (y[line-1] - y[line - 2]) / h[line - 2] + h[line - 2] / 2 * fn;
	}
	m1.A = A1;
	m1.line = line;
	m1.subtract();
	vector<double>t = m1.get_result();
	return t;
}
int main()
{
	vector<double> x, y, L, U, D, h;
	int line;
	cout << "请输入已知x的个数：";
	int n;
	cin >> n;
	cout << "请输入x,y:";
	double t1, t2;
	for (int i = 0; i < n; i++)
	{
		cin >> t1;
		cin >> t2;
		x.push_back(t1);
		y.push_back(t2);
	}
	get_paras(x, y, L, U, D, h);
	line = D.size();
	int n1;//n是选择的第几边界条件
	n1=method();
	if (n1 == 1)
	{
		vector<double> result1 = method1(L, U, D, line);
		output(result1, x, y, h);
	}
	else
	{
		vector<double> result2 = method2(h, y, L, U, D, line + 2);
		output(result2, x, y, h);
	}
	return 0;
}

