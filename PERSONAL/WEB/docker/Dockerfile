FROM php:8.4.6RC1-fpm

RUN apt-get update && apt-get install -y \
  git \
  curl \
  zip \
  vim \
  unzip

WORKDIR /var/www

# Composer for autoloader
RUN curl -sS https://getcomposer.org/installer | php -- --install-dir=/usr/local/bin --filename=composer

# PDO - MySQL driver
RUN docker-php-ext-install pdo pdo_mysql
