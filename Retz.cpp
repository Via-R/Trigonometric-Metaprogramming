//Автор: Рець Вадим Олександрович, група К22
//Точність розрахунку ряду Тейлора відбувається до 510 члену ряду, в силу обмеженості можливостей компілятора відносно кількості рекурсій для шаблону, точність результату - 6 знаків після коми

#include <iostream>
#include <iomanip>
#include <cmath>
# define M_PI		3.14159265358979323846
#define precision	100000000
using namespace std;


template<int N, int D>
class Exp {
public:static inline constexpr int getRes(){
		return constexpr(static_cast<int>(precision*ExpSeries<N, D, 511, 1>::sum()));
	}
};
template<int N, int D, int J, int K>
class ExpSeries {
public:
	enum { go = (K + 1 != J) };
	constexpr static inline float sum()
	{

		return 1 + static_cast<float>(N) / static_cast<float>(D) / K*ExpSeries<N*go, D*go, J*go, (K + 1)*go>::sum();
	}
};
template<>
class ExpSeries<0, 0, 0, 0> {
public:constexpr static inline float sum() {
	return 0;
}
};


template<int N, int D>
class Sin {
public:static inline constexpr int getRes() {
	return constexpr(static_cast<int>(precision * (static_cast<float>(N) / static_cast<float>(D)*SinSeries<N, D, 510, 0>::res())));
}
};
template<int N, int D, int J, int K>
class SinSeries {
public:enum { allow = (K + 1) != J };
	   constexpr static inline float res() {
		   return 1 - (static_cast<float>(N) / static_cast<float>(D))*(static_cast<float>(N) / static_cast<float>(D)) / (2 * K + 2) / (2 * K + 3)*SinSeries<N*allow, D*allow, J*allow, (K + 1)*allow>::res();
	   }
};
template<>
class SinSeries<0, 0, 0, 0> {
public: constexpr static inline float res() {
	return 1;
}
};


template<int N, int D>
class Cos {
public:static inline constexpr int getRes() {
	return constexpr(static_cast<int>(precision * CosSeries<N, D, 510, 0>::res()));
}
};
template<int N, int D, int J, int K>
class CosSeries {
public:enum { allow = (K + 1) != J };
	   constexpr static inline float res() {
		   return 1 - (static_cast<float>(N) / static_cast<float>(D))*(static_cast<float>(N) / static_cast<float>(D)) / (2 * K + 2) / (2 * K + 1)*CosSeries<N*allow, D*allow, J*allow, (K + 1)*allow>::res();
	   }
};
template<>
class CosSeries<0, 0, 0, 0> {
public: constexpr static inline float res() {
	return 1;
}
};


template<int N, int D>
class ArcSin {
public:static inline constexpr int getRes() {
	return constexpr(static_cast<int>(precision * static_cast<float>(N) / static_cast<float>(D)*ArcSinSeries<N, D, 509, 0>::res()));
}
};
template<int N, int D, int J, int K>
class ArcSinSeries {
public:enum { allow = (K + 1) != J };
	   constexpr static inline float res() {
		   return 1 + ((2. * K + 1)*(2. * K + 1)) / (2. * (K + 1)*(2. * K + 3)) * (static_cast<float>(N) / static_cast<float>(D)) * (static_cast<float>(N) / static_cast<float>(D)) * ArcSinSeries<N*allow, D*allow, J*allow, (K + 1)*allow>::res();
	   }
};
template<>
class ArcSinSeries<0, 0, 0, 0> {
public: constexpr static inline float res() {
	return 1.;
}
};


template<int N, int D>
class Ln {
public:static inline constexpr int getRes() {
	return constexpr(static_cast<int>(precision * static_cast<float>(N) / static_cast<float>(D)*LnSeries<N, D, 511, 1>::res()));
}
};
template<int N, int D, int J, int K>
class LnSeries {
public:enum { allow = (K + 1) != J };
	   constexpr static inline float res() {
		   return 1. - (static_cast<float>(N) / static_cast<float>(D) * static_cast<float>(K)) / (static_cast<float>(K + 1))  * LnSeries<N*allow, D*allow, J*allow, (K + 1)*allow>::res();
	   }
};
template<>
class LnSeries<0, 0, 0, 0> {
public: constexpr static inline float res() {
	return 1;
}
};


template<int N, int D>
class ArcCos {
public:static inline constexpr int getRes() {
	return constexpr(static_cast<int>(precision * (M_PI / 2. - static_cast<float>(ArcSin<N, D>::getRes())/precision)));
}
};


int main() {
	const int n = -1;
	const int m = 2;
	
	constexpr int expCalculated = Exp<n, m>::getRes();
	constexpr int arcCosCalculated = ArcCos<expCalculated, precision>::getRes();
	constexpr int sinCalculated = Sin<arcCosCalculated, precision>::getRes();
	constexpr int cosCalculated = Cos<sinCalculated, precision>::getRes();
	constexpr int lnCalculated = Ln<cosCalculated-precision, precision>::getRes();

	float result = (float)lnCalculated / precision;
	float wantedResult = log(cos(sin(acos(exp((float)n / m)))));
	cout << "Calculating expression: log( cos( sin( acos( exp( N / M ) ) ) ) ), where N = " << n << ", M = " << m << ".\n";
	cout << fixed << setprecision(10);
	cout << "Result using custom methods:\t" << result << endl;
	cout << "Result using library \"cmath\":\t"<< wantedResult << endl;
	system("pause");
	return 0;
}