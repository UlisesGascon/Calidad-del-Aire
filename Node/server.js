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
                //console.log(datos);
                var datosSerie = JSON.parse(datos);
                
                // Amoniaco
                if (datosSerie.amoniaco.valido){
                    console.log("Amoniaco: " + datosSerie.amoniaco.valor + "ppm"  );
                } else {
                    console.log("Amoniaco: ERROR!!")
                };
                
                // Dióxido de Carbono
                if (datosSerie.dioxidoDeCarbono.valido){
                    console.log("Dióxido de Carbono: " + datosSerie.dioxidoDeCarbono.valor + "ppm"  );
                } else {
                    console.log("Dióxido de Carbono: ERROR!!")
                }

                // Óxidos de Nitrógeno
                if (datosSerie.oxidosDeNitrogeno.valido){
                    console.log("Óxidos de Nitrógeno: " + datosSerie.oxidosDeNitrogeno.valor + "ppm"  );
                } else {
                    console.log("Óxidos de Nitrógeno: ERROR!!")
                }

                // Hidrógeno
                if (datosSerie.hidrogeno.valido){
                    console.log("Hidrógeno: " + datosSerie.hidrogeno.valor + "ppm"  );
                } else {
                    console.log("Hidrógeno: ERROR!!")
                }

                // Monóxido de Carbono
                if (datosSerie.monoxidoDeCarbono.valido){
                    console.log("Monóxido de Carbono: " + datosSerie.monoxidoDeCarbono.valor + "ppm"  );
                } else {
                    console.log("Monóxido de Carbono: ERROR!!")
                }

                // Propano
                if (datosSerie.propano.valido){
                    console.log("Propano: " + datosSerie.propano.valor + "ppm"  );
                } else {
                    console.log("Propano: ERROR!!")
                }

                // Metano
                if (datosSerie.metano.valido){
                    console.log("Metano: " + datosSerie.metano.valor + "ppm"  );
                } else {
                    console.log("Metano: ERROR!!")
                }

                // GLP
                if (datosSerie.glp.valido){
                    console.log("GLP: " + datosSerie.glp.valor + "ppm"  );
                } else {
                    console.log("GLP: ERROR!!")
                }

                // Alcohol
                if (datosSerie.alcohol.valido){
                    console.log("Alcohol: " + datosSerie.alcohol.valor + "Mg/L"  );
                } else {
                    console.log("Alcohol: ERROR!!")
                }

                // Humedad
                if (datosSerie.humedad.valido){
                    console.log("Humedad: " + datosSerie.humedad.valor + "%"  );
                } else {
                    console.log("Humedad: ERROR!!")
                }

                // Temperatura
                if (datosSerie.temperatura.valido){
                    console.log("Temperatura: " + datosSerie.temperatura.valor + "°C"  );
                } else {
                    console.log("Temperatura: ERROR!!")
                }

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