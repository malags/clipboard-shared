const express = require('express')
const path = require('path')
const app = express()

app.use(express.json())

const port = 9000

app.locals.clipboard = "test"

app.get('/clipboard', (req, res) => {
    res.json(app.locals.clipboard)
})

app.post('/clipboard', (req, res) => {
    app.locals.clipboard = req.body
    res.sendStatus(200)
})

app.use(express.static(path.join(__dirname,'build')))

app.listen(port, () => {
  console.log(`App listening at http://localhost:${port}`)
})
