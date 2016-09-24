//color class simplified from valve sdk......
class Color
{
private:
	int R, G, B, A;
public:
	Color() : R(0), G(0), B(0), A(0) {}
	Color(int r, int g, int b, int a) : R(r), G(g), B(b), A(a) {}
	Color(int r, int g, int b) : R(r), G(g), B(b), A(255) {}
	int r() { return R; }
	int g() { return G; }
	int b() { return B; }
	int a() { return A; }
	Color& operator = (Color& c)
	{
		R = c.r();
		G = c.g();
		B = c.b();
		A = c.a();
		return *this;
	}
};