
#define NUM_LIGHTS 4

/////////////
// GLOBALS //
/////////////
cbuffer  MatrixBuffer: register(b0)
{
	matrix worldMatrix;
	matrix viewMatrix;
	matrix projectionMatrix;
};

cbuffer LightPositionBuffer
{
	float4 lightPosition[NUM_LIGHTS];
};

//////////////
// TYPEDEFS //
//////////////
struct VertexInputType
{
	float4 position : SV_Position;
	float3 normal : NORMAL;
	float3 tangent : TANGENT;
	float2 tex : TEXCOORD;
};

struct PixelInputType
{
	float4 position : SV_Position;
	float2 tex : TEXCOORD0;
	float3 normal : NORMAL;
	float3 lightPos1 : TEXCOORD1;
	float3 lightPos2 : TEXCOORD2;
	float3 lightPos3 : TEXCOORD3;
	float3 lightPos4 : TEXCOORD4;
};


////////////////////////////////////////////////////////////////////////////////
// Vertex Shader
////////////////////////////////////////////////////////////////////////////////
PixelInputType VS(VertexInputType input)
{
	PixelInputType output;
	float4 worldPosition;


	// Change the position vector to be 4 units for proper matrix calculations.
	input.position.w = 1.0f;

	// Calculate the position of the vertex against the world, view, and projection matrices.
	output.position = mul(input.position, worldMatrix);
	output.position = mul(output.position, viewMatrix);
	output.position = mul(output.position, projectionMatrix);

	// Store the texture coordinates for the pixel shader.
	output.tex = input.tex;

	// Calculate the normal vector against the world matrix only.
	output.normal = mul(input.normal, (float3x3)worldMatrix);

	// Normalize the normal vector.
	output.normal = normalize(output.normal);

	// Calculate the position of the vertex in the world.
	worldPosition = mul(input.position, worldMatrix);
	//The position of the four lights in the world in relation to the vertex must be calculated, normalized, and then sent into the pixel shader.

	// Determine the light positions based on the position of the lights and the position of the vertex in the world.
	output.lightPos1.xyz = lightPosition[0].xyz - worldPosition.xyz;
	output.lightPos2.xyz = lightPosition[1].xyz - worldPosition.xyz;
	output.lightPos3.xyz = lightPosition[2].xyz - worldPosition.xyz;
	output.lightPos4.xyz = lightPosition[3].xyz - worldPosition.xyz;

	// Normalize the light position vectors.
	output.lightPos1 = normalize(output.lightPos1);
	output.lightPos2 = normalize(output.lightPos2);
	output.lightPos3 = normalize(output.lightPos3);
	output.lightPos4 = normalize(output.lightPos4);

	return output;
}


/////////////
// GLOBALS //
/////////////
Texture2D shaderTexture;
SamplerState SampleType;
//This array is for the four colors of the four point lights.

cbuffer LightColorBuffer
{
	float4 diffuseColor[NUM_LIGHTS];
};


////////////////////////////////////////////////////////////////////////////////
// Pixel Shader
////////////////////////////////////////////////////////////////////////////////
float4 PS(PixelInputType input) : SV_TARGET
{
	float4 textureColor;
	float lightIntensity1, lightIntensity2, lightIntensity3, lightIntensity4;
	float4 color, color1, color2, color3, color4;
	//	The light intensity for each of the four point lights is calculated using the position of the light and the normal vector.

	// Calculate the different amounts of light on this pixel based on the positions of the lights.
	lightIntensity1 = saturate(dot(input.normal, input.lightPos1));
	lightIntensity2 = saturate(dot(input.normal, input.lightPos2));
	lightIntensity3 = saturate(dot(input.normal, input.lightPos3));
	lightIntensity4 = saturate(dot(input.normal, input.lightPos4));
	//The amount of color contributed by each point light is calculated from the intensity of the point light and the light color.

	// Determine the diffuse color amount of each of the four lights.
	color1 = diffuseColor[0] * lightIntensity1;
	color2 = diffuseColor[1] * lightIntensity2;
	color3 = diffuseColor[2] * lightIntensity3;
	color4 = diffuseColor[3] * lightIntensity4;

	// Sample the texture pixel at this location.
	textureColor = shaderTexture.Sample(SampleType, input.tex);
	//Finally add all the four point lights together to get the final light color for this pixel.Multiply the summed light color by the texture pixel and the calculations are complete.

	// Multiply the texture pixel by the combination of all four light colors to get the final result.
	color = saturate(color1 + color2 + color3 + color4) * textureColor;

	return color;
}
