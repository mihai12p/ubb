import random

if __name__ == '__main__':
    num_problems = 10
    num_countries = 5
    country_codes = [f"C{i+1}" for i in range(num_countries)]
    id_ranges = {f"C{i+1}": range(i*100 + 100, i*100 + 199 + 1) for i in range(num_countries)}

    for country_code in country_codes:
        for problem_number in range(1, num_problems + 1):
            ids = list(id_ranges[country_code])
            num_participants = random.randint(80, 100)

            file_name = f"Rezultate{country_code}_P{problem_number}.txt"
            with open(file_name, "w") as file:
                for _ in range(num_participants):
                    if not ids:
                        break

                    participant_id = random.choice(ids)
                    ids.remove(participant_id)
                    score = random.choice([-1, *range(1, 101)])
                    file.write(f"{participant_id} {score}\n")