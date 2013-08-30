local L = Level.class

function Level.loadObject( asset )
  local table = dofile( 'Assets/' .. asset .. '.lua' )
  local o = ClassTable[ table['class'] ]()

  o:loadSettings( table )

  return o
end
Load = Level.loadObject

function L:addAsset( asset )
  local o = Level.loadObject( asset )
  self:add(o)
  return o
end

function L:add( object )
  object:visible( true )
  self:addSprite( object )
  return object
end

print( 'Class Level Loaded' )

