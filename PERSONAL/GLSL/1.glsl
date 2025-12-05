#ifdef GL_ES
  precision mediump float;
#endif



uniform float u_time;
uniform vec2 u_resolution;
const float PI = 3.14159;



vec3 color_correct(vec3 v);



void main()
{
  // Normalize coordinates (0 to 1)
  vec2 uv = gl_FragCoord.xy / u_resolution.xy;

  // Center the coordinates (-0.5 to 0.5), correct aspect
  vec2 centered = uv - 0.5;
  centered.x *= u_resolution.x / u_resolution.y;

  // Distance from center
  float dist = length(centered);//length(atan(sin(centered) * 50.));

  // Animated expanding circles using sine
  float speed = 4.;
  float frequency = 5.0; // number of rings per unit distance
  float wave = .5 + sin(
    2. * PI * frequency * dist - u_time * speed
  );

  // Optional: make edges sharper
  float ring = smoothstep(0.5, 0.5, wave);

  vec3 color = color_correct(
    vec3(
      ring - cos(u_time),
      ring,
      ring
    )
  );

  gl_FragColor = vec4(color, 1.0);
}



vec3 color_correct(vec3 v)
{
  return v / 2.;
}
