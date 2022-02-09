var root = document.querySelector(':root');
var lowerLimit = -20;
var upperLimit = 120;
var u = upperLimit - lowerLimit;
var radius = 60;
var transform = radius / 3;

function toRadians (angle) {
    return angle * (Math.PI / 180);
}

function computeY(temp) {
    return -(radius - change) * Math.cos(toRadians(((temp - lowerLimit) / u) * 360)) + transform;
}

function computeX(temp) {
    x = Math.sqrt((radius*radius)-(temp*temp));
    if (temp > (upperLimit-lowerLimit)) {
        return x;
    } else {
        return -1 * x;
    }
}

function computeAngle(temp) {
    null;
}

function setTempGuage(temp) {
    root.style.setProperty('--pointertop', computeY(80) + "%");
    root.style.setProperty('--pointerleft', computeX(80) + "%");
}