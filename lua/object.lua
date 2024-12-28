-- 定义一个名为 Person 的类
local Person = {}
Person.__index = Person

-- 定义 Person 类的构造函数
function Person.new(name, age)
    local self = setmetatable({}, Person)
    self.name = name
    self.age = age
    return self
end

-- 定义 Person 类的方法
function Person.sayHello(self)
    print("Hello, my name is " .. self.name .. " and I am " .. self.age .. " years old.")
end

function Person:getAge()
    return self.age
end

-- 创建 Person 类的实例
local person1 = Person.new("Alice", 25)
local person2 = Person.new("Bob", 30)

-- 调用实例的方法
person1:sayHello()  -- 输出: Hello, my name is Alice and I am 25 years old.
person2:sayHello()  -- 输出: Hello, my name is Bob and I am 30 years old.

-- 访问实例的属性
print(person1.name)  -- 输出: Alice
print(person2:getAge())  -- 输出: 30
