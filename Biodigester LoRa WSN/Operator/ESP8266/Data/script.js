/*
    Written by Aqilla Rahman Musyaffa
*/

//Get current sensor readings when the page loads  
window.addEventListener('load', getReadings);

//=============================FIRST BIO GAUGE=============================
// Create Temperature Gauge
var B1gaugeTemp = new LinearGauge
(
	{
		renderTo: 'b1-gauge-temperature',
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
var B1gaugePress = new RadialGauge
(
	{
		renderTo: 'b1-gauge-pressure',
		width: 200,
		height: 200,
		units: "Tekanan (Bar)",
		minValue: 0,
		maxValue: 3,
		colorValueBoxRect: "#049faa",
		colorValueBoxRectEnd: "#049faa",
		colorValueBoxBackground: "#f1fbfc",
		valueInt: 1,
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

// Create CO2 Gauge
var B1gaugeCarbon = new RadialGauge
(
	{
		renderTo: 'b1-gauge-carbon',
		width: 200,
		height: 200,
		units: "PPM",
		minValue: 0,
		maxValue: 30000,
		colorValueBoxRect: "#049faa",
		colorValueBoxRectEnd: "#049faa",
		colorValueBoxBackground: "#f1fbfc",
		valueInt: 1,
		majorTicks: 
		[
			"0",
			"5000",
			"10000",
			"15000",
			"20000",
			"25000",
			"30000",
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

var B1gaugeMethane = new RadialGauge
(
	{
		renderTo: 'b1-gauge-methane',
		width: 200,
		height: 200,
		units: "PPM",
		minValue: 0,
		maxValue: 30000,
		colorValueBoxRect: "#049faa",
		colorValueBoxRectEnd: "#049faa",
		colorValueBoxBackground: "#f1fbfc",
		valueInt: 1,
		majorTicks: 
		[
			"0",
			"5000",
			"10000",
			"15000",
			"20000",
			"25000",
			"30000",
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
var B1gaugePH = new RadialGauge
(
	{
		renderTo: 'b1-gauge-pH',
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
var B1gaugeLevel = new LinearGauge
(
	{
		renderTo: 'b1-gauge-level',
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
var B1gaugePress2 = new RadialGauge
(
	{
		renderTo: 'b1-gauge-pressure-2',
		width: 170,
		height: 170,
		units: "Tekanan (Bar)",
		minValue: 0,
		maxValue: 3,
		colorValueBoxRect: "#049faa",
		colorValueBoxRectEnd: "#049faa",
		colorValueBoxBackground: "#f1fbfc",
		valueInt: 1,
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

// Create Volume Gauge
var B1gaugeVolume = new RadialGauge
(
	{
		renderTo: 'b1-gauge-volume',
		width: 170,
		height: 170,
		units: "Volume Gas (L)",
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

//=============================SECOND BIO GAUGE=============================
// Create Temperature Gauge
var B2gaugeTemp = new LinearGauge
(
	{
		renderTo: 'b2-gauge-temperature',
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
var B2gaugePress = new RadialGauge
(
	{
		renderTo: 'b2-gauge-pressure',
		width: 200,
		height: 200,
		units: "Tekanan (Bar)",
		minValue: 0,
		maxValue: 3,
		colorValueBoxRect: "#049faa",
		colorValueBoxRectEnd: "#049faa",
		colorValueBoxBackground: "#f1fbfc",
		valueInt: 1,
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

// Create CO2 Gauge
var B2gaugeCarbon = new RadialGauge
(
	{
		renderTo: 'b2-gauge-carbon',
		width: 200,
		height: 200,
		units: "PPM",
		minValue: 0,
		maxValue: 30000,
		colorValueBoxRect: "#049faa",
		colorValueBoxRectEnd: "#049faa",
		colorValueBoxBackground: "#f1fbfc",
		valueInt: 1,
		majorTicks: 
		[
			"0",
			"5000",
			"10000",
			"15000",
			"20000",
			"25000",
			"30000",
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

var B2gaugeMethane = new RadialGauge
(
	{
		renderTo: 'b2-gauge-methane',
		width: 200,
		height: 200,
		units: "PPM",
		minValue: 0,
		maxValue: 30000,
		colorValueBoxRect: "#049faa",
		colorValueBoxRectEnd: "#049faa",
		colorValueBoxBackground: "#f1fbfc",
		valueInt: 1,
		majorTicks: 
		[
			"0",
			"5000",
			"10000",
			"15000",
			"20000",
			"25000",
			"30000",
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
var B2gaugePH = new RadialGauge
(
	{
		renderTo: 'b2-gauge-pH',
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
var B2gaugeLevel = new LinearGauge
(
	{
		renderTo: 'b2-gauge-level',
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
var B2gaugePress2 = new RadialGauge
(
	{
		renderTo: 'b2-gauge-pressure-2',
		width: 170,
		height: 170,
		units: "Tekanan (Bar)",
		minValue: 0,
		maxValue: 3,
		colorValueBoxRect: "#049faa",
		colorValueBoxRectEnd: "#049faa",
		colorValueBoxBackground: "#f1fbfc",
		valueInt: 1,
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

// Create Volume Gauge
var B2gaugeVolume = new RadialGauge
(
	{
		renderTo: 'b2-gauge-volume',
		width: 170,
		height: 170,
		units: "Volume Gas (L)",
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

//=============================THIRD BIO GAUGE=============================
// Create Temperature Gauge
var B3gaugeTemp = new LinearGauge
(
	{
		renderTo: 'b3-gauge-temperature',
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
var B3gaugePress = new RadialGauge
(
	{
		renderTo: 'b3-gauge-pressure',
		width: 200,
		height: 200,
		units: "Tekanan (Bar)",
		minValue: 0,
		maxValue: 3,
		colorValueBoxRect: "#049faa",
		colorValueBoxRectEnd: "#049faa",
		colorValueBoxBackground: "#f1fbfc",
		valueInt: 1,
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

// Create CO2 Gauge
var B3gaugeCarbon = new RadialGauge
(
	{
		renderTo: 'b3-gauge-carbon',
		width: 200,
		height: 200,
		units: "PPM",
		minValue: 0,
		maxValue: 30000,
		colorValueBoxRect: "#049faa",
		colorValueBoxRectEnd: "#049faa",
		colorValueBoxBackground: "#f1fbfc",
		valueInt: 1,
		majorTicks: 
		[
			"0",
			"5000",
			"10000",
			"15000",
			"20000",
			"25000",
			"30000",
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

var B3gaugeMethane = new RadialGauge
(
	{
		renderTo: 'b3-gauge-methane',
		width: 200,
		height: 200,
		units: "PPM",
		minValue: 0,
		maxValue: 30000,
		colorValueBoxRect: "#049faa",
		colorValueBoxRectEnd: "#049faa",
		colorValueBoxBackground: "#f1fbfc",
		valueInt: 1,
		majorTicks: 
		[
			"0",
			"5000",
			"10000",
			"15000",
			"20000",
			"25000",
			"30000",
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
var B3gaugePH = new RadialGauge
(
	{
		renderTo: 'b3-gauge-pH',
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
var B3gaugeLevel = new LinearGauge
(
	{
		renderTo: 'b3-gauge-level',
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
var B3gaugePress2 = new RadialGauge
(
	{
		renderTo: 'b3-gauge-pressure-2',
		width: 170,
		height: 170,
		units: "Tekanan (Bar)",
		minValue: 0,
		maxValue: 3,
		colorValueBoxRect: "#049faa",
		colorValueBoxRectEnd: "#049faa",
		colorValueBoxBackground: "#f1fbfc",
		valueInt: 1,
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

// Create Volume Gauge
var B3gaugeVolume = new RadialGauge
(
	{
		renderTo: 'b3-gauge-volume',
		width: 170,
		height: 170,
		units: "Volume Gas (L)",
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

//=============================FOURTH BIO GAUGE=============================
// Create Temperature Gauge
var B4gaugeTemp = new LinearGauge
(
	{
		renderTo: 'b4-gauge-temperature',
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
var B4gaugePress = new RadialGauge
(
	{
		renderTo: 'b4-gauge-pressure',
		width: 200,
		height: 200,
		units: "Tekanan (Bar)",
		minValue: 0,
		maxValue: 3,
		colorValueBoxRect: "#049faa",
		colorValueBoxRectEnd: "#049faa",
		colorValueBoxBackground: "#f1fbfc",
		valueInt: 1,
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

// Create CO2 Gauge
var B4gaugeCarbon = new RadialGauge
(
	{
		renderTo: 'b4-gauge-carbon',
		width: 200,
		height: 200,
		units: "PPM",
		minValue: 0,
		maxValue: 30000,
		colorValueBoxRect: "#049faa",
		colorValueBoxRectEnd: "#049faa",
		colorValueBoxBackground: "#f1fbfc",
		valueInt: 1,
		majorTicks: 
		[
			"0",
			"5000",
			"10000",
			"15000",
			"20000",
			"25000",
			"30000",
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

var B4gaugeMethane = new RadialGauge
(
	{
		renderTo: 'b4-gauge-methane',
		width: 200,
		height: 200,
		units: "PPM",
		minValue: 0,
		maxValue: 30000,
		colorValueBoxRect: "#049faa",
		colorValueBoxRectEnd: "#049faa",
		colorValueBoxBackground: "#f1fbfc",
		valueInt: 1,
		majorTicks: 
		[
			"0",
			"5000",
			"10000",
			"15000",
			"20000",
			"25000",
			"30000",
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
var B4gaugePH = new RadialGauge
(
	{
		renderTo: 'b4-gauge-pH',
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
var B4gaugeLevel = new LinearGauge
(
	{
		renderTo: 'b4-gauge-level',
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
var B4gaugePress2 = new RadialGauge
(
	{
		renderTo: 'b4-gauge-pressure-2',
		width: 170,
		height: 170,
		units: "Tekanan (Bar)",
		minValue: 0,
		maxValue: 3,
		colorValueBoxRect: "#049faa",
		colorValueBoxRectEnd: "#049faa",
		colorValueBoxBackground: "#f1fbfc",
		valueInt: 1,
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

// Create Volume Gauge
var B4gaugeVolume = new RadialGauge
(
	{
		renderTo: 'b4-gauge-volume',
		width: 170,
		height: 170,
		units: "Volume Gas (L)",
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

//=============================FIFTH BIO GAUGE=============================
// Create Temperature Gauge
var B5gaugeTemp = new LinearGauge
(
	{
		renderTo: 'b5-gauge-temperature',
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
var B5gaugePress = new RadialGauge
(
	{
		renderTo: 'b5-gauge-pressure',
		width: 200,
		height: 200,
		units: "Tekanan (Bar)",
		minValue: 0,
		maxValue: 3,
		colorValueBoxRect: "#049faa",
		colorValueBoxRectEnd: "#049faa",
		colorValueBoxBackground: "#f1fbfc",
		valueInt: 1,
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

// Create CO2 Gauge
var B5gaugeCarbon = new RadialGauge
(
	{
		renderTo: 'b5-gauge-carbon',
		width: 200,
		height: 200,
		units: "PPM",
		minValue: 0,
		maxValue: 30000,
		colorValueBoxRect: "#049faa",
		colorValueBoxRectEnd: "#049faa",
		colorValueBoxBackground: "#f1fbfc",
		valueInt: 1,
		majorTicks: 
		[
			"0",
			"5000",
			"10000",
			"15000",
			"20000",
			"25000",
			"30000",
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

var B5gaugeMethane = new RadialGauge
(
	{
		renderTo: 'b5-gauge-methane',
		width: 200,
		height: 200,
		units: "PPM",
		minValue: 0,
		maxValue: 30000,
		colorValueBoxRect: "#049faa",
		colorValueBoxRectEnd: "#049faa",
		colorValueBoxBackground: "#f1fbfc",
		valueInt: 1,
		majorTicks: 
		[
			"0",
			"5000",
			"10000",
			"15000",
			"20000",
			"25000",
			"30000",
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
var B5gaugePH = new RadialGauge
(
	{
		renderTo: 'b5-gauge-pH',
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
var B5gaugeLevel = new LinearGauge
(
	{
		renderTo: 'b5-gauge-level',
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
var B5gaugePress2 = new RadialGauge
(
	{
		renderTo: 'b5-gauge-pressure-2',
		width: 170,
		height: 170,
		units: "Tekanan (Bar)",
		minValue: 0,
		maxValue: 3,
		colorValueBoxRect: "#049faa",
		colorValueBoxRectEnd: "#049faa",
		colorValueBoxBackground: "#f1fbfc",
		valueInt: 1,
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

// Create Volume Gauge
var B5gaugeVolume = new RadialGauge
(
	{
		renderTo: 'b5-gauge-volume',
		width: 170,
		height: 170,
		units: "Volume Gas (L)",
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

function openBio (evt, bioName)
{
	var i, tabcontent, tablinks;
	
	tabcontent = document.getElementsByClassName("tabcontent");
	for (i = 0; i < tabcontent.length; i++)
	{
		tabcontent[i].style.display = "none";
	}
	
	tablinks = document.getElementsByClassName("tablinks");
	for (i = 0; i < tablinks.length; i++) 
	{
		tablinks[i].className = tablinks[i].className.replace(" active", "");
	}
	
	document.getElementById(bioName).style.display = "block";
	evt.currentTarget.className += " active";
}	

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
			
			var B1lv 		= myObj.B1level;
			var B1press1 	= myObj.B1pressure1;
			var B1press2 	= myObj.B1pressure2;
			var B1vol 		= myObj.B1volume;
			var B1pH 		= myObj.B1ph;
			var B1methane	= myObj.B1CH4;
			var B1carbon	= myObj.B1CO2;
			var B1temp 		= myObj.B1temperature;
			B1gaugeLevel.value = B1lv;
			B1gaugePress.value = B1press1;
			B1gaugePress2.value = B1press2;
			B1gaugeVolume.value = B1vol;
			B1gaugePH.value = B1pH;
			B1gaugeMethane.value = B1methane;
			B1gaugeCarbon.value = B1carbon;
			B1gaugeTemp.value = B1temp;
			
			var B2lv 		= myObj.B2level;
			var B2press1 	= myObj.B2pressure1;
			var B2press2 	= myObj.B2pressure2;
			var B2vol 		= myObj.B2volume;
			var B2pH 		= myObj.B2ph;
			var B2methane	= myObj.B2CH4;
			var B2carbon	= myObj.B2CO2;
			var B2temp 		= myObj.B2temperature;
			B2gaugeLevel.value = B2lv;
			B2gaugePress.value = B2press1;
			B2gaugePress2.value = B2press2;
			B2gaugeVolume.value = B2vol;
			B2gaugePH.value = B2pH;
			B2gaugeMethane.value = B2methane;
			B2gaugeCarbon.value = B2carbon;
			B2gaugeTemp.value = B2temp;
			
			var B3lv 		= myObj.B3level;
			var B3press1 	= myObj.B3pressure1;
			var B3press2 	= myObj.B3pressure2;
			var B3vol 		= myObj.B3volume;
			var B3pH 		= myObj.B3ph;
			var B3methane	= myObj.B3CH4;
			var B3carbon	= myObj.B3CO2;
			var B3temp 		= myObj.B3temperature;
			B3gaugeLevel.value = B3lv;
			B3gaugePress.value = B3press1;
			B3gaugePress2.value = B3press2;
			B3gaugeVolume.value = B3vol;
			B3gaugePH.value = B3pH;
			B3gaugeMethane.value = B3methane;
			B3gaugeCarbon.value = B3carbon;
			B3gaugeTemp.value = B3temp;
			
			var B4lv 		= myObj.B4level;
			var B4press1 	= myObj.B4pressure1;
			var B4press2 	= myObj.B4pressure2;
			var B4vol 		= myObj.B4volume;
			var B4pH 		= myObj.B4ph;
			var B4methane	= myObj.B4CH4;
			var B4carbon	= myObj.B4CO2;
			var B4temp 		= myObj.B4temperature;
			B4gaugeLevel.value = B4lv;
			B4gaugePress.value = B4press1;
			B4gaugePress2.value = B4press2;
			B4gaugeVolume.value = B4vol;
			B4gaugePH.value = B4pH;
			B4gaugeMethane.value = B4methane;
			B4gaugeCarbon.value = B4carbon;
			B4gaugeTemp.value = B4temp;
			
			var B5lv 		= myObj.B5level;
			var B5press1 	= myObj.B5pressure1;
			var B5press2 	= myObj.B5pressure2;
			var B5vol 		= myObj.B5volume;
			var B5pH 		= myObj.B5ph;
			var B5methane	= myObj.B5CH4;
			var B5carbon	= myObj.B5CO2;
			var B5temp 		= myObj.B5temperature;
			B5gaugeLevel.value = B5lv;
			B5gaugePress.value = B5press1;
			B5gaugePress2.value = B5press2;
			B5gaugeVolume.value = B5vol;
			B5gaugePH.value = B5pH;
			B5gaugeMethane.value = B5methane;
			B5gaugeCarbon.value = B5carbon;
			B5gaugeTemp.value = B5temp;
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
		
		var B1lv 		= myObj.B1level;
		var B1press1 	= myObj.B1pressure1;
		var B1press2 	= myObj.B1pressure2;
		var B1vol 		= myObj.B1volume;
		var B1pH 		= myObj.B1ph;
		var B1methane	= myObj.B1CH4;
		var B1carbon	= myObj.B1CO2;
		var B1temp 		= myObj.B1temperature;
		B1gaugeLevel.value = B1lv;
		B1gaugePress.value = B1press1;
		B1gaugePress2.value = B1press2;
		B1gaugeVolume.value = B1vol;
		B1gaugePH.value = B1pH;
		B1gaugeMethane.value = B1methane;
		B1gaugeCarbon.value = B1carbon;
		B1gaugeTemp.value = B1temp;
			
		var B2lv 		= myObj.B2level;
		var B2press1 	= myObj.B2pressure1;
		var B2press2 	= myObj.B2pressure2;
		var B2vol 		= myObj.B2volume;
		var B2pH 		= myObj.B2ph;
		var B2methane	= myObj.B2CH4;
		var B2carbon	= myObj.B2CO2;
		var B2temp 		= myObj.B2temperature;
		B2gaugeLevel.value = B2lv;
		B2gaugePress.value = B2press1;
		B2gaugePress2.value = B2press2;
		B2gaugeVolume.value = B2vol;
		B2gaugePH.value = B2pH;
		B2gaugeMethane.value = B2methane;
		B2gaugeCarbon.value = B2carbon;
		B2gaugeTemp.value = B2temp;
			
		var B3lv 		= myObj.B3level;
		var B3press1 	= myObj.B3pressure1;
		var B3press2 	= myObj.B3pressure2;
		var B3vol 		= myObj.B3volume;
		var B3pH 		= myObj.B3ph;
		var B3methane	= myObj.B3CH4;
		var B3carbon	= myObj.B3CO2;
		var B3temp 		= myObj.B3temperature;
		B3gaugeLevel.value = B3lv;
		B3gaugePress.value = B3press1;
		B3gaugePress2.value = B3press2;
		B3gaugeVolume.value = B3vol;
		B3gaugePH.value = B3pH;
		B3gaugeMethane.value = B3methane;
		B3gaugeCarbon.value = B3carbon;
		B3gaugeTemp.value = B3temp;
			
		var B4lv 		= myObj.B4level;
		var B4press1 	= myObj.B4pressure1;
		var B4press2 	= myObj.B4pressure2;
		var B4vol 		= myObj.B4volume;
		var B4pH 		= myObj.B4ph;
		var B4methane	= myObj.B4CH4;
		var B4carbon	= myObj.B4CO2;
		var B4temp 		= myObj.B4temperature;
		B4gaugeLevel.value = B4lv;
		B4gaugePress.value = B4press1;
		B4gaugePress2.value = B4press2;
		B4gaugeVolume.value = B4vol;
		B4gaugePH.value = B4pH;
		B4gaugeMethane.value = B4methane;
		B4gaugeCarbon.value = B4carbon;
		B4gaugeTemp.value = B4temp;
			
		var B5lv 		= myObj.B5level;
		var B5press1 	= myObj.B5pressure1;
		var B5press2 	= myObj.B5pressure2;
		var B5vol 		= myObj.B5volume;
		var B5pH 		= myObj.B5ph;
		var B5methane	= myObj.B5CH4;
		var B5carbon	= myObj.B5CO2;
		var B5temp 		= myObj.B5temperature;
		B5gaugeLevel.value = B5lv;
		B5gaugePress.value = B5press1;
		B5gaugePress2.value = B5press2;
		B5gaugeVolume.value = B5vol;
		B5gaugePH.value = B5pH;
		B5gaugeMethane.value = B5methane;
		B5gaugeCarbon.value = B5carbon;
		B5gaugeTemp.value = B5temp;
	}, false);
}
