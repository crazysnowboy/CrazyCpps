#version 330 core

// Input vertex data, different for all executions of this shader.
layout(location = 0) in  vec3 Vertices;
layout(location = 1) in  vec3 vertNormal;
layout(location = 2) in  vec2 UVs;


uniform mat4 ProjectionModelViewMatrix;

out vec3 fragVert;
out vec2 fragTexCoord;
out vec3 fragNormal;

void main(){



    // Pass some variables to the fragment shader
    fragTexCoord = UVs;
    fragNormal = vertNormal;
    fragVert = Vertices;


	gl_Position =  ProjectionModelViewMatrix  * vec4(Vertices,1);


}

