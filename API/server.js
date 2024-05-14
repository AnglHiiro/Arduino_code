const express = require('express')
const app = express()

app.use(express.urlencoded({ extended: false}))
app.use(express.json({ limit: '5mb' }))

app.use(require('./routes/index'))

const port = 5000

app.listen(port, () => {
    console.log("[SERVER]: Starting server...");
})
.on('listening', () => {
    console.log(`[SERVER]: Server started on ${port}`);
})
.on('error', (err) => {
    console.log(`[SERVER]: Error trying to start the server on ${port}`);
})
.on('close', () => {
    console.log('[SERVER]: The server was closed.');
})
