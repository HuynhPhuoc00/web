const fan = document.querySelector('.fan');
const blades = document.querySelectorAll('.blade');
const speedControl = document.getElementById('fan-speed');

function setBladeSpeed(speed) {
  blades.forEach((blade, i) => {
    blade.style.transform = `rotate(${speed * (i + 1) * 6}deg)`;
  });
}

speedControl.addEventListener('input', () => {
  setBladeSpeed(speedControl.value);
});

setBladeSpeed(speedControl.value);
