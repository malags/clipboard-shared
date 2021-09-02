const path = require('path');
const HtmlWebPackPlugin = require("html-webpack-plugin");
const webpack = require("webpack");

require('dotenv').config();

module.exports = {
    entry: './src/index.js',
    output: {
        filename: 'main.js',
        path: path.resolve(__dirname, 'build'),
        publicPath: '/'
    },
    module: {
        rules: [
            {
                test: /\.(js|jsx)$/,
                exclude: /node_modules/,
                use: {
                    loader: "babel-loader"
                }
            },
            {
                test: /\.html$/,
                use: [
                    {
                        loader: "html-loader"
                    }
                ]
            }
        ]
    },
    devServer: {
        historyApiFallback: true,
        port: 8080,
        open: true,
        hot: true,
        host: '0.0.0.0'
    },
    plugins: [
        new HtmlWebPackPlugin({
            template: "./src/index.html",
            filename: "./index.html"
        }),
        new webpack.DefinePlugin({
            'process.env.HOST_URL': JSON.stringify(process.env.HOST_URL)
        }),
    ],
    mode: "production"
};