#version 330 core


uniform sampler2D Texture;
uniform mat4 ProjectionModelViewMatrix;

uniform struct Light
{
   vec3 position;
   vec3 intensities; //a.k.a the color of the light
} light;

in vec2 fragTexCoord;
in vec3 fragNormal;
in vec3 fragVert;

out vec4 finalColor;


void main(){

    //calculate normal in world coordinates
    mat3 normalMatrix = transpose(inverse(mat3(ProjectionModelViewMatrix)));
    vec3 normal = -normalize(normalMatrix * fragNormal);
    //calculate the location of this fragment (pixel) in world coordinates
    vec3 fragPosition = vec3(ProjectionModelViewMatrix * vec4(fragVert, 1));
    //calculate the vector from this pixels surface to the light source
    vec3 surfaceToLight = light.position - fragPosition;
    //calculate the cosine of the angle of incidence
    float brightness = dot(normal, surfaceToLight) / (length(surfaceToLight) * length(normal));
    brightness = clamp(brightness, 0, 1);
    //calculate final color of the pixel, based on:
    // 1. The angle of incidence: brightness
    // 2. The color/intensities of the light: light.intensities
    // 3. The texture and texture coord: texture(tex, fragTexCoord)
    vec4 surfaceColor = texture(Texture, fragTexCoord);
    finalColor = vec4(brightness * light.intensities * surfaceColor.bgr, surfaceColor.a);
//    finalColor = vec4(surfaceColor.bgr, surfaceColor.a);


}