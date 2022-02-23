const ctx = document.getElementById('chart').getContext('2d');
var myChart = new Chart(ctx, {
    type: "line",
    data: {
        labels: [1, 2, 3, 4, 5, 6, 7, 8, 9],
        datasets: [
            {
                label: "Dataset 1",
                data: [1, 2, 5, 4, 6, 10, 5, 8, 2],
                borderColor: ["rgba(255, 0, 0, 1)"],
                backgroundColor: ["rgba(255, 0, 0, 0.2)"],
            }
        ]
    },
    options: {
        responsive: true,
        plugins: {
            legend: {
                position: "top",
            },
            title: {
                display: false,
                text: "Example Line Chart"
            }
        }
    }
});