//Get current sensor readings when the page loads  
window.addEventListener('load', getReadings);

// Create Temperature Gauge
var gaugeTemp = new LinearGauge
(
	{
		renderTo: 'gauge-temperature',
		width: 100,
		height: 190,
		units: "Temperatur (C)",
		minValue: 0,
		startAngle: 90,
		ticksAngle: 180,
		maxValue: 50,
		colorValueBoxRect: "#049faa",
		colorValueBoxRectEnd: "#049faa",
		colorValueBoxBackground: "#f1fbfc",
		valueDec: 1,
		valueInt: 1,
		majorTicks: 
		[
			"0",
			"10",
			"20",
			"30",
			"40",
			"50"
		],
		
		minorTicks: 4,
		strokeTicks: true,
		highlights: 
		[
			{
				
				"from": 10,
				"to": 20,
				"color": "#00d5ff"
				
			},
			{
				
				"from": 20,
				"to": 30,
				"color": "#1aff00"
				
			},
			{
				
				"from": 30,
				"to": 50,
				"color": "#ff0014"
				
			}
		],
		
		colorPlate: "#fff",
		colorBarProgress: "#CC2936",
		colorBarProgressEnd: "#049faa",
		borderShadowWidth: 0,
		borders: false,
		needleType: "arrow",
		needleWidth: 2,
		needleCircleSize: 7,
		needleCircleOuter: true,
		needleCircleInner: false,
		animationDuration: 1500,
		animationRule: "linear",
		barWidth: 10,
	}
).draw();

// Create Pressure Gauge
var gaugePress = new RadialGauge
(
	{
		renderTo: 'gauge-pressure',
		width: 200,
		height: 200,
		units: "Tekanan (Bar)",
		minValue: 0,
		maxValue: 3,
		colorValueBoxRect: "#049faa",
		colorValueBoxRectEnd: "#049faa",
		colorValueBoxBackground: "#f1fbfc",
		valueInt: 2,
		majorTicks: 
		[
			"0",
			"0.5",
			"1",
			"1.5",
			"2",
			"2.5",
			"3",
		],
		
		minorTicks: 4,
		strokeTicks: true,
		highlights: 
		[
			{
				"from": 1.75,
				"to": 2.5,
				"color": "#f26050"
			},
			{
				"from": 2.5,
				"to": 3,
				"color": "#e01600"
			},
		],
  
		colorPlate: "#fff",
		borderShadowWidth: 0,
		borders: false,
		needleType: "line",
		colorNeedle: "#007F80",
		colorNeedleEnd: "#007F80",
		needleWidth: 2,
		needleCircleSize: 3,
		colorNeedleCircleOuter: "#007F80",
		needleCircleOuter: true,
		needleCircleInner: false,
		animationDuration: 1500,
		animationRule: "linear"
	}
).draw();

// Create pH Gauge
var gaugePH = new RadialGauge
(
	{
		renderTo: 'gauge-pH',
		width: 200,
		height: 200,
		units: "pH",
		minValue: 0,
		maxValue: 14,
		colorValueBoxRect: "#049faa",
		colorValueBoxRectEnd: "#049faa",
		colorValueBoxBackground: "#f1fbfc",
		valueInt: 1,
		majorTicks: 
		[
			"0",
			"2",
			"4",
			"6",
			"8",
			"10",
			"12",
			"14"
		],
		
		minorTicks: 4,
		strokeTicks: true,
		highlights: 
		[
			{
				"from": 6.5,
				"to": 7.5,
				"color": "#28d900"
			},
			
			{
				"from": 7.5,
				"to": 14,
				"color": "#03C0C1"
			},
			
			{
				"from": 0,
				"to": 6.5,
				"color": "#ff1100"
			}
		],
  
		colorPlate: "#fff",
		borderShadowWidth: 0,
		borders: false,
		needleType: "line",
		colorNeedle: "#007F80",
		colorNeedleEnd: "#007F80",
		needleWidth: 2,
		needleCircleSize: 3,
		colorNeedleCircleOuter: "#007F80",
		needleCircleOuter: true,
		needleCircleInner: false,
		animationDuration: 1500,
		animationRule: "linear"
	}
).draw();

// Create Water Level Gauge
var gaugeLevel = new LinearGauge
(
	{
		renderTo: 'gauge-level',
		width: 100,
		height: 190,
		units: "Level Limbah",
		minValue: 0,
		startAngle: 90,
		ticksAngle: 180,
		maxValue: 1,
		colorValueBoxRect: "#049faa",
		colorValueBoxRectEnd: "#049faa",
		colorValueBoxBackground: "#f1fbfc",
		valueDec: 1,
		valueInt: 1,
		majorTicks: 
		[
			"Kosong",
			"Penuh"
		],
		
		minorTicks: 0,
		strokeTicks: true,
		highlights: 
		[
		],
		colorPlate: "#fff",
		colorBarProgress: "#fff",
		colorBarProgressEnd: "#fff",
		borderShadowWidth: 0,
		borders: false,
		needleType: "arrow",
		needleWidth: 5,
		needleCircleSize: 7,
		needleCircleOuter: true,
		needleCircleInner: false,
		animationDuration: 1500,
		animationRule: "linear",
		barWidth: 7,
	}
).draw();

// Create Pressure2 Gauge
var gaugePress2 = new RadialGauge
(
	{
		renderTo: 'gauge-pressure-2',
		width: 170,
		height: 170,
		units: "Tekanan (Bar)",
		minValue: 0,
		maxValue: 3,
		colorValueBoxRect: "#049faa",
		colorValueBoxRectEnd: "#049faa",
		colorValueBoxBackground: "#f1fbfc",
		valueInt: 2,
		majorTicks: 
		[
			"0",
			"0.5",
			"1",
			"1.5",
			"2",
			"2.5",
			"3",
		],
		
		minorTicks: 4,
		strokeTicks: true,
		highlights: 
		[
			{
				"from": 1.75,
				"to": 2.5,
				"color": "#f26050"
			},
			{
				"from": 2.5,
				"to": 3,
				"color": "#e01600"
			},
		],
  
		colorPlate: "#fff",
		borderShadowWidth: 0,
		borders: false,
		needleType: "line",
		colorNeedle: "#007F80",
		colorNeedleEnd: "#007F80",
		needleWidth: 2,
		needleCircleSize: 3,
		colorNeedleCircleOuter: "#007F80",
		needleCircleOuter: true,
		needleCircleInner: false,
		animationDuration: 1500,
		animationRule: "linear"
	}
).draw();

// Create Flow Gauge
var gaugeFlow = new RadialGauge
(
	{
		renderTo: 'gauge-flow',
		width: 170,
		height: 170,
		units: "Laju Gas (L/Min)",
		minValue: 0,
		maxValue: 30,
		colorValueBoxRect: "#049faa",
		colorValueBoxRectEnd: "#049faa",
		colorValueBoxBackground: "#f1fbfc",
		valueInt: 1,
		majorTicks: 
		[
			"0",
			"5",
			"10",
			"15",
			"20",
			"25",
			"30"
		],
		
		minorTicks: 4,
		strokeTicks: true,
		highlights: 
		[
			/*
			{
				"from": 80,
				"to": 100,
				"color": "#03C0C1"
			}
			*/
		],
  
		colorPlate: "#fff",
		borderShadowWidth: 0,
		borders: false,
		needleType: "line",
		colorNeedle: "#007F80",
		colorNeedleEnd: "#007F80",
		needleWidth: 2,
		needleCircleSize: 3,
		colorNeedleCircleOuter: "#007F80",
		needleCircleOuter: true,
		needleCircleInner: false,
		animationDuration: 1500,
		animationRule: "linear"
	}
).draw();

// Function to get current readings on the webpage when it loads for the first time
function getReadings()
{
	var xhr = new XMLHttpRequest();
	xhr.onreadystatechange = function() 
	{
		if (this.readyState == 4 && this.status == 200) 
		{
			var myObj = JSON.parse(this.responseText);
			console.log(myObj);
			var temp = myObj.temperature;
			var press = myObj.pressure;
			var pH = myObj.ph;
			var lv = myObj.level;
			var press2 = myObj.pressure2;
			var fw = myObj.flow;
			gaugeTemp.value = temp;
			gaugePress.value = press;
			gaugePH.value = pH;
			gaugeLevel.value = lv;
			gaugePress2.value = press2;
			gaugeFlow.value = fw;
		}
	}; 
	
	xhr.open("GET", "/readings", true);
	xhr.send();
}

if (!!window.EventSource) 
{
	var source = new EventSource('/events');
  
	source.addEventListener('open', function(e) 
	{
		console.log("Events Connected");
	}, false);

	source.addEventListener('error', function(e) 
	{
		if (e.target.readyState != EventSource.OPEN) 
		{
			console.log("Events Disconnected");
		}
	}, false);
  
	source.addEventListener('message', function(e) 
	{
		console.log("message", e.data);
	}, false);
  
	source.addEventListener('new_readings', function(e) 
	{
		console.log("new_readings", e.data);
		var myObj = JSON.parse(e.data);
		console.log(myObj);
		gaugeTemp.value = myObj.temperature;
		gaugePress.value = myObj.pressure;
		gaugePH.value = myObj.ph;
		gaugeLevel.value = myObj.level;
		gaugePress2.value = myObj.pressure2;
		gaugeFlow.value = myObj.flow;
	}, false);
}