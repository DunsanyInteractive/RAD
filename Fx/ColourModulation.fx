float4x4 World;
float4x4 View;

struct VertexOut
{
    float4 Pos : POSITION;
    float4 Color : COLOR;
	float2 textureuv :TEXCOORD;
};

VertexOut VShader(float4 Pos : POSITION, float4 colour :COLOR, float2 textureCoord :TEXCOORD)
{
    VertexOut Vert = (VertexOut)0;
 	float4x4 Transform;

	Transform = mul(World, View);
 	 	
 	Vert.Pos = mul(Pos, Transform );
 	
  

    Vert.Color = colour;
	Vert.textureuv = textureCoord;
    return Vert;
}

technique FirstTechnique
{
    pass FirstPass
    {
        Lighting = FALSE;
        ZEnable = TRUE;
   
        VertexShader = compile vs_2_0 VShader();
    }
}