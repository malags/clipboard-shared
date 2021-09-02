FROM node

WORKDIR /app

EXPOSE 9000

COPY . /app

RUN npm ci

RUN npm run build

CMD ["npm", "start"]