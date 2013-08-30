ClassTable['Animation'] = Animation.new
local class = Animation.class
local parent = Sprite.class

--[ Inheritance ]--
setmetatable( class, parent );
class.super = Sprite.class

function class:loadSettings( table )
  self:frames( table['reel_length'] )
 
  local row_dim = table['row_dimension']
  self:rowDimensions( row_dim[1], row_dim[2] )

  --[ Set frame last ]--
  if not table['frame'] then self:frame( table['frame'] ) end

  self.super.loadSettings( self, table )
end

print( 'Class Animation Loaded' )

