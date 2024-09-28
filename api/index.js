import express from "express";
import bodyParser from "body-parser";
import cors from "cors";

const app = express();
const port = 3000;

// Configurar CORS
app.use((req, res, next) => {
  res.header("Access-Control-Allow-Origin", "*"); // Permitir todas las solicitudes
  res.header("Access-Control-Allow-Headers", "Origin, X-Requested-With, Content-Type, Accept");
  next();
});

var info = [1, 2, 3];
app.use(bodyParser.urlencoded({ extended: true }));

app.get("/data", (req, res) => {
  res.json(info);
});

app.post("/make", (req, res) => {
  const { value } = req.query; // Cambiado de req.query a req.body

  if (!value) {
    return res.status(400).json({ message: 'Missing required field: value' });
  }

  info.push(Number(value)); // Asegúrate de que sea un número
  res.status(200).json({
    message: 'Data received successfully',
    data: {
        value,
        info
    },
  });
});

app.listen(port, () => {
  console.log(`Successfully started server on port ${port}.`);
});
