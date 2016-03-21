var serialport = require('serialport'),
	SerialPort = require("serialport").SerialPort,
	puerto = process.argv[2];

if (puerto) {

    var serialPort = new SerialPort(puerto, {
        encoding: 'utf8',
        parser: serialport.parsers.readline("\n"),
        baudrate: 9600
    });

    serialPort.open(function(error) {
        if (error) {
            console.log('Error al arrancar: ' + error);
        } else {
            
            console.log('Comunicación establecida con éxito!');
            console.log('Iniciando la recepción de datos:');
            serialPort.on('data', function(datos) {
                console.log(datos);
                var datosSerie = JSON.parse(datos);
                // console.log(datosSerie);
           
            });

        }
    });

} else {

    serialport.list(function(err, ports) {
        ports.forEach(function(port) {
            console.log(port.comName);
        });
    });

}