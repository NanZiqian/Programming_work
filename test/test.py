class Person:
	def __call__(self,name):
		print('__call__: '+name)
	def hello(self,name):
		print("hello! "+name)

person = Person()
person("alpha")
person.hello("chalie")