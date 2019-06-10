local c = require 'test'
local __table__ = {
	'01010100', '01100101', '01110011',
	'01110100', '0001010', '0001010',
	'01001000', '01100101', '01101100',
	'01101100', '01101111', '00100000',
	'01110111', '01101111', '01110010',
	'01101100', '01100100', '0001010'
}
c.print(c.sum(5, 5))
c.print('\n')

c.print(c.multiply(5, 5))
c.print('\n')

c.print(c.len(__table__));
c.print('\n')

c.print("hello", "world")
c.print('\n')

c.print(__table__)
c.print('\n')
c.print('\n')

for i=1, #__table__ do
	c.print(c.get_char_binary(__table__[i]))
end
