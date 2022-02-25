var activeElements = document.getElementsByClassName("active");
var timespan = activeElements[1].id;
var datatype = activeElements[2].id;

async function getGraphData(datatype, timespan) {  //gets the weather data from the server webhook and extracts the value from json
    let url = '/get_graph_data/' + timespan + '/' + datatype;
    let obj = null;
    
    try {
        obj = await (await fetch(url)).json();
    } catch(e) {
        console.log('error');
    }
    
    return [Object.values(obj)[0], Object.values(obj)[1]];
}

var data = await getGraphData(datatype, timespan);
var times = data[0];
var datapoints = data[1];

const ctx = document.getElementById('chart').getContext('2d');
var myChart = new Chart(ctx, {
    type: "line",
    data: {
        labels: times,
        datasets: [
            {
                label: datatype,
                data: datapoints,
                borderColor: ["rgba(255, 0, 0, 1)"],
                backgroundColor: ["rgba(255, 0, 0, 0.2)"],
            }
        ]
    },
    options: {
        responsive: true,
        plugins: {
            legend: {
                display: false,
            },
            title: {
                display: false,
                text: "Example Line Chart"
            }
        }
    }
});