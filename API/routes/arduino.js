const express = require('express')
const router = express.Router()
router.use(express.json())

router.post('/servo1', async (req, res) => {
    try {
        const { angulo } = req.body;
        res.json({
            status: 200,
            message: `servo 1 ${angulo} grados.`
        });
    } catch (error) {
        res.json({ status: 500, error: error.message });
    }
});

router.post('/led', async (req, res) => {
    try {
        const { estado } = req.body;
        res.json({
            status: 200,
            message: `LED ${estado}.`
        });
    } catch (error) {
        res.json({ status: 500, error: error.message });
    }
});

router.post('/servo2', async (req, res) => {
    try {
        const { angulo } = req.body;
        res.json({
            status: 200,
            message: `servo 2 ${angulo} grados.`
        });
    } catch (error) {
        res.json({ status: 500, error: error.message });
    }
});

router.get('/temperatura', async (req, res) => {
    try {
        const temperatura = 25;
        res.json({
            status: 200,
            message: `${temperatura} grados.`
        });
    } catch (error) {
        res.json({ status: 500, error: error.message });
    }
});

router.get('/luz', async (req, res) => {
    try {
        const luz = 200;
        res.json({
            status: 200,
            message: `Lectura actual de luz: ${luz}.`
        });
    } catch (error) {
        res.json({ status: 500, error: error.message });
    }
});

router.get('/movimiento', async (req, res) => {
    try {
        const distancia = 30;
        res.json({
            status: 200,
            message: `Movimiento detectado a ${distancia}cm.`
        });
    } catch (error) {
        res.json({ status: 500, error: error.message });
    }
});

module.exports = router