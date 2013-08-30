ClassTable['Button'] = Button.new
local class = Button.class
local parent = Animation.class

--[ Inheritance ]--
setmetatable( class, parent );
class.super = parent.class

function class:loadSettings( table )
  self.super.loadSettings( self, table )
end

print( 'Class Button Loaded' )

