module.exports = {
    configureWebpack: {
        module: {
            rules: [
                {
                    test: /\.md$/i,
                    loader: "raw-loader",
                },
            ],
        },
    },
};
