class Node:
	def isfree(self, x):
		pass
	def replace(self, x, t):
		pass
	def noconf(self, x, t):
		pass
	def __str__(self):
		pass

class Var(Node):
	def __init__(self, x):
		self.x = x
	def isfree(self, x):
		return self.x == x
	def replace(self, x, t):
		return t if self.x == x else self
	def noconf(self, x, t):
		return True
	def __str__(self):
		return self.x

class Func(Node):
	def __init__(self, f, args):
		self.f = f
		self.args = args
	def isfree(self, x):
		for arg in self.args:
			if arg.isfree(x):
				return True
		return False
	def replace(self, x, t):
		return Func(self.f, [arg.replace(x, t) for arg in self.args])
	def noconf(self, x, t):
		return True
	def __str__(self):
		return self.f + ''.join(map(str, self.args))

class ForAll(Node):
	def __init__(self, y, f):
		self.y = y
		self.f = f
	def isfree(self, x):
		return x != self.y and self.f.isfree(x)
	def replace(self, x, t):
		return self if x == self.y else ForAll(self.y, self.f.replace(x, t))
	def noconf(self, x, t):
		return not self.isfree(x) or (not t.isfree(self.y) and self.f.noconf(x, t))
	def __str__(self):
		return 'A' + self.y + str(self.f)

class Not(Node):
	def __init__(self, f):
		self.f = f
	def isfree(self, x):
		return self.f.isfree(x)
	def replace(self, x, t):
		return Not(self.f.replace(x, t))
	def noconf(self, x, t):
		return self.f.noconf(x, t)
	def __str__(self):
		return 'N' + str(self.f)

class Imply(Node):
	def __init__(self, f, g):
		self.f = f
		self.g = g
	def isfree(self, x):
		return self.f.isfree(x) or self.g.isfree(x)
	def replace(self, x, t):
		return Imply(self.f.replace(x, t), self.g.replace(x, t))
	def noconf(self, x, t):
		return self.f.noconf(x, t) and self.g.noconf(x, t)
	def __str__(self):
		return str(self.f) + 'I' + str(self.g)

class Parent(Node):
	def __init__(self, f):
		self.f = f
	def isfree(self, x):
		return self.f.isfree(x)
	def replace(self, x, t):
		return Parent(self.f.replace(x, t))
	def noconf(self, x, t):
		return self.f.noconf(x, t)
	def __str__(self):
		return f'({self.f})'


class Parser:
	def __init__(self, f, sym):
		self.f = f
		self.sym = sym
		self.pos = 0
	def next(self):
		return None if self.pos >= len(self.f) else self.f[self.pos]
	def match(self, tok=None):
		if tok is not None and self.f[self.pos] != tok:
			raise Exception
		self.pos += 1
		return self.f[self.pos - 1]
	def formula(self):
		if self.next() == 'A':
			self.match('A')
			y = self.match()
			return ForAll(y, self.top())
		if self.next() == 'N':
			self.match('N')
			return Not(self.top())
		if self.next() == '(':
			self.match('(')
			f = self.top()
			self.match(')')
			return Parent(f)
		return self.term()
	def term(self):
		if self.next() in self.sym:
			f = self.match()
			args = [self.term() for i in range(self.sym[f])]
			return Func(f, args)
		return Var(self.match())
	def top(self):
		f = self.formula()
		while self.next() == 'I':
			self.match('I')
			f = Imply(f, self.formula())
		return f
	def parse(self):
		return self.top()


def solve():
	F = input().strip()
	sym = {}
	m = int(input())
	for i in range(m):
		f, n = input().strip().split()
		sym[f] = int(n)
	F = Parser(F, sym).parse()
	q = int(input())
	for i in range(q):
		t, x = input().strip().split()
		t = Parser(t, sym).term()
		if F.noconf(x, t):
			print('Y')
			print(F.replace(x, t))
		else:
			print('N')


T = int(input())
for _ in range(T):
	solve()