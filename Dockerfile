FROM node:16.8-slim

WORKDIR /app

COPY . /app

RUN npm ci

CMD ["npm", "start"]