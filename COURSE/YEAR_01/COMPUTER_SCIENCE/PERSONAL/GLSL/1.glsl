#ifdef GL_ES
  precision mediump float;
#endif

uniform float u_time;
uniform vec2 u_resolution;

#define uv gl_FragCoord.xy / u_resolution.xy

void main()
{
  vec3 color = vec3(uv / 6., 0);
  gl_FragColor = vec4(color, 1.);
}