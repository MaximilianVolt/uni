FROM rust:latest

WORKDIR /app

# Current folder -> containerized current folder (app)
COPY . .

RUN cargo install cargo-watch

CMD ["/bin/bash"]
