#version 330 core

uniform vec3 viewPos;
uniform vec3 lightPos;

in vec3 worldPos;
in vec3 worldNorm;

out vec3 color;
 
void main() {
	vec3 V = normalize(viewPos - worldPos);
	vec3 L = normalize(lightPos - worldPos);
	vec3 H = normalize(L + V);
	
	float diff = 0.8 * max(0, dot(L, worldNorm));
	float spec = pow(max(0, dot(H, worldNorm)), 32);
	spec *= (spec > 0.4)? 1.0 : 0.0;
	
	float edge = (dot(V, worldNorm) >  0.2) ? 1 : 0;
	vec3 ambClr = vec3(0, 0.1, 0.1);
	vec3 diffClr = floor(8 * diff * vec3(0.0, 1.0, 1.0)) / 8;
	vec3 specClr = spec * vec3(1.0, 1.0, 1.0);
    color = edge * (ambClr + diffClr + specClr);
}
