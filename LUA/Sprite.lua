ClassTable['Sprite'] = Sprite.new
local class = Sprite.class

function class:loadSettings( table )
  self:image( 'Assets/' .. table['image'] )

  local rect = table['sourceRect']
  local size = table['size']
 
  if rect then
	self:sourceRect(rect[1], rect[2], rect[3], rect[4])
	size = size or {rect[3] - rect[1], rect[4] - rect[2]}
  end
  if size then self:size(size[1], size[2]) end

  self:visible( true )
end

print( 'Class Sprite Loaded' )

