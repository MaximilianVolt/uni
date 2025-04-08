let elem = document.getElementById("text");



(color_change = async(e) => {
  e.style.color = generate_color(Date.now() / 10 % 360, 100, 75);
  setTimeout(color_change, 50, e);
})(elem);




function generate_placeholder_color()
{
  return generate_color(Math.random() * 360, 100, 75);
}



function generate_color(h, s, l)
{
  return `hsl(${h}, ${s}%, ${l}%)`;
}


