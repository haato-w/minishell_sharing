build:
	source ../docker-environments/development_base_for_mac/build_script.sh
up:
	source ../docker-environments/development_base_for_mac/up_script.sh

in:
	docker start minishell-env
	docker exec -it minishell-env bash
