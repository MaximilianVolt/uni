const PH_LEVEL_MIDDLE = 7;

let phLevels = document.querySelectorAll('.ph-level');

for (let level = 0; level < phLevels.length; ++level)
{
  let h = getPhLevelHue(phLevels.length - level)
    , s = Math.abs(PH_LEVEL_MIDDLE - level) / PH_LEVEL_MIDDLE * 100
    , l = 100 - math_dual_proportion(s, 75, 95, 85, 100) / 2.5;
  ;

  phLevels.item(level).style.backgroundColor = `hsl(${h}, ${s}%, ${l}%)`;
}



function getPhLevelHue(level)
{
  // Hues (blue, 'none', purple)
  return [293, 0, 185][
    1 + Number(level > PH_LEVEL_MIDDLE) - Number(level < PH_LEVEL_MIDDLE)
  ];
}



function math_dual_proportion(a, a1, a2, b1, b2)
{
  return (a - a1) / (a2 - a1) * (b2 - b1) + b1;
}




let a = new Audio("./FM1.ogg");


a.autoplay = true;
a.loop = true;

setInterval(() => console.log("Hello"), 100);